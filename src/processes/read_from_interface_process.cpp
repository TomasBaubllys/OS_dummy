#include "../../include/processes/read_from_interface_process.h"
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

            return Process_State::BLOCKED;
        }
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_F$: {
            if(this -> buffer.rfind(RMI_FILE_INPUT, 0) == 0) {

            }
        }
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_HARD_DISK:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_FILE_EXISTS:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_READ_AND_DIVIDE_FILE:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_SUPERVISOR_MEMORY:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_COPY_BYTES_TO_SUPERVISOR_MEMORY:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_RELEASE_TASK_IN_SUPERVISOR:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_$:
            if(this -> buffer.rfind(RMI_SYS_COMMAND, 0)) {

            }
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_RELEASE_SYSTEM_COMMAND:
            break;
        default:
            break;
    }
}