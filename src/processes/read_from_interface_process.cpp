#include "../../include/processes/read_from_interface_process.h"
#include "../../include/processes/job_governor_process.h"
#include <iostream>

Read_From_Interface_Process::Read_From_Interface_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username):
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::READ_FROM_INTERFACE_PRIORITY){

}

Read_From_Interface_Process::~Read_From_Interface_Process() {

}

Process_State Read_From_Interface_Process::execute(){
    switch (this -> step) {
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE: {
            if(this -> owns_resource(Resource_Type::FROM_USER_INTERFACE)) {
                this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_F$;
                std::getline(std::cin, this -> buffer);
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::FROM_USER_INTERFACE);
            return Process_State::BLOCKED;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_F$:
            if(this -> buffer.rfind(RMI_FILE_INPUT, 0) == 0) {
                Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_HARD_DISK;
            }
            this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_$;
            return Process_State::READY;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_HARD_DISK:
            if(this -> owns_resource(Resource_Type::HARD_DISK)) {
                this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_FILE_EXISTS;
                return Process_State::READY;
            }
            return Process_State::BLOCKED;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_FILE_EXISTS: {
            std::string file_name = this -> buffer.substr(2);
            Hard_Disk* hd = this -> kernel -> get_hard_disk();
            File_Entry* file_entries;
            uint32_t file_count = read_file_entries(hd, &file_entries);

            bool match_found = false;
            for(uint32_t i = 0; i < file_count; ++i) {
                if(strcmp(file_entries[i].file_name, file_name.c_str()) == 0) {
                    match_found = true;
                    break;
                }
            }

            if(!match_found) {
                // FREE CURRENT RESOURCES
                this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE;
            }
            else {
                this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_READ_AND_DIVIDE_FILE;
            }

            return Process_State::READY;
        }
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_READ_AND_DIVIDE_FILE:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_SUPERVISOR_MEMORY:
            if(this -> owns_resource(Resource_Type::SUPERVISOR_MEMORY)) {
                this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_COPY_BYTES_TO_SUPERVISOR_MEMORY;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::SUPERVISOR_MEMORY);
            return Process_State::BLOCKED;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_COPY_BYTES_TO_SUPERVISOR_MEMORY:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_RELEASE_TASK_IN_SUPERVISOR:
            this -> kernel -> release_resource(Resource_Type::TASK_IN_SUPERVISOR);
            this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE;

            return Process_State::READY;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_$:
            if(this -> buffer.rfind(RMI_SYS_COMMAND, 0) == 0) {
                this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_RELEASE_SYSTEM_COMMAND;
            }
            else {
                Job_Governor_Process* jg = this -> kernel -> current_console_holder; 
                // if current console holder is null, ignore the buffer
                if(jg == nullptr) {
                    this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE;
                    // RELEASE THE OWNED RESOURCES

                    return Process_State::READY;
                }
                
                this -> kernel -> release_resource_for(Resource_Type::USER_INPUT, jg -> get_unique_id(), this -> buffer);
                this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE;
                // jg -> vm_input -> set_buffer(this -> buffer);
                // this -> kernel -> release_resource(jg -> vm_input);
            }
            return Process_State::READY; 
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_RELEASE_SYSTEM_COMMAND:
            this -> kernel -> release_resource(Resource_Type::SYSTEM_COMMAND, this -> buffer.substr(1));
            this -> step = Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE;
            
            /*
                RELEASE HARD DISK
                and others?
            */
            
            return Process_State::READY;
        default:
            break;
    }
}