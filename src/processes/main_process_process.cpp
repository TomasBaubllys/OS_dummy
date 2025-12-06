#include "../../include/processes/main_process_process.h"
#include "../../include/kernel.h"
#include <iostream>

Main_Process_Process::Main_Process_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::MAIN_PROCESS_PRIORITY){

}

Main_Process_Process::~Main_Process_Process(){

}

Process_State Main_Process_Process::execute(){
    switch (this -> step){
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND:
            if(this -> owns_resource(Resource_Type::SYSTEM_COMMAND)) {
                this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_PIE_IN_THE_OVEN_FREE;
                return Process_State::READY; 
            }
            
            this -> kernel -> request_resource(this, Resource_Type::SYSTEM_COMMAND);
            return Process_State::BLOCKED;

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_PIE_IN_THE_OVEN_FREE:
            if(this -> owns_resource(Resource_Type::PIE_IN_THE_OVEN)) {
                /**
                 *  check buffer if it contains 0 or 1 
                 * DO SOMETHING
                 */
            }
            
            this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_ITS_SHUT_DOWN; 
            return Process_State::READY;

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_ITS_SHUT_DOWN: {
            std::string command = this -> get_owned_resource(Resource_Type::SYSTEM_COMMAND) -> get_buffer();
            if(command.rfind(RMI_SHUTDOWN_COMMAND, 0) == 0) {
                this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CREATE_RESOURCE_MOS_END;
            }
            else {
                this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_ITS_KILL;
            }

            return Process_State::READY;
        }

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CREATE_RESOURCE_MOS_END:
            this -> kernel -> init_resource(Resource_Type::MOS_END, this);
            this -> kernel -> release_resource(Resource_Type::MOS_END);
            this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND;
            return Process_State::READY;

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_ITS_KILL: {
            // should not be null lol (upon crash check here)
            std::string command = this -> get_owned_resource(Resource_Type::SYSTEM_COMMAND) -> get_buffer();
            if(command.rfind(RMI_KILL_COMMAND, 0) == 0) {
                this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_REMOVE_PROCESS_JOB_GOVERNOR_1;
            }
            else {
                this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_NONEXISTING_SYSTEM_COMMAND;
            }

            return Process_State::READY;
        }

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_REMOVE_PROCESS_JOB_GOVERNOR_1: {
            // figure out the id
            std::string command = this -> get_owned_resource(Resource_Type::SYSTEM_COMMAND) -> get_buffer();
            
            // request the kernel to kill it
            size_t pos = std::string(RMI_KILL_COMMAND).size();
            uint32_t id;
            try {
                id = stoi(command.substr(pos));
            }
            catch(const std::exception &e) {
                // idk release the resource and signal that incorrect sdadsafa

            } 

            this -> kernel -> request_to_kill(id);
            
            /**
             *  GET RID OF THE OWNED RESOURCE!!!!!
             * 
             */

            this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND;
            return Process_State::READY;
        }

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_NONEXISTING_SYSTEM_COMMAND:
            this -> kernel -> release_resource(Resource_Type::STRING_IN_MEMORY, STR_MEM_UNKNOWN_SYS_COM_ERR_MSG);
            this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND;

            // find the system command an return it to the owner
            for(auto it = this -> owned_resources.begin(); it != this -> owned_resources.end(); ++it) {
                if((*it) -> get_resource_type() == Resource_Type::SYSTEM_COMMAND) {
                    this -> kernel -> return_resource_to_owner((*it));
                    // a lil risky, but its fine:)
                    this -> owned_resources.erase(it);
                    break;
                }
            }

            return Process_State::READY;

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_RUNTIME_0:
            /*
                IDK WHAT TO DO
            */
            this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CREATE_PROCESS_JOB_OVERNOR_WITH_PIE_IN_THE_OVEN_RESOURCE;
            return Process_State::READY;

        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CREATE_PROCESS_JOB_OVERNOR_WITH_PIE_IN_THE_OVEN_RESOURCE: {
            uint32_t jg_id = this -> kernel -> create_process<Job_Governor_Process>(this, {}, SYSTEM_USERNAME);
            this -> kernel -> init_resource(Resource_Type::PIE_IN_THE_OVEN, this);
            this -> kernel -> release_resource_for(Resource_Type::PIE_IN_THE_OVEN, jg_id);
            this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND;
            return Process_State::READY;
        }
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_REMOVE_PROCESS_JOB_GOVERNER_2:
            /*
                COME HERE ONLY IF YOU FIGURE OUT WHAT TO DO WITH THE IF TIME NOT 0 command....
            */
            return Process_State::READY;
        default:
            break;
    }

    return Process_State::BLOCKED_STOPPED;
}