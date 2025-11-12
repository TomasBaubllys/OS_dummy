#include "../include/read_from_interface_process.h"

Read_From_Interface_Process::Read_From_Interface_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username):
    Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username){

}

Read_From_Interface_Process::~Read_From_Interface_Process(){

}

int8_t Read_From_Interface_Process::execute(){
    switch (this -> current_step)
    {
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE:
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_F$:
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
            break;
        case Read_From_Interface_Process_Steps::READ_FROM_INTERFACE_RELEASE_SYSTEM_COMMAND:
            break;
        default:
            break;
    }
}