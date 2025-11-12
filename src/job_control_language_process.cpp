#include "../include/job_control_language_process.h"

Job_Control_Language_Process::Job_Control_Language_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username){

} 

Job_Control_Language_Process::~Job_Control_Language_Process(){

}

int8_t Job_Control_Language_Process::execute(){
    switch (this -> current_step){
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_BLOCKED_WAIT_FOR_TASK_IN_SUPERVISOR:
            /* code */
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_INITIALIZE_PROGRAM_LIST:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_TAKE_BLOCK_FROM_SUPERVISOR_MEMORY_1:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_LOS:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_ATTACH_BLOCK_TO_PROGRAM_LIST:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_TAKE_BLOCK_FROM_SUPERVISOR_MEMORY_2:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_BYE_OR_IS_IT_LAST_BLOCK:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_BYE:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_ATTACH_BOCK_TO_PROGRAM_LIST_AND_CREATE_RESOURCE_LOADER_PACKAGE:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_PIE_IN_THE_OVEN:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_BYE_NOT_FOUND:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_LOS_NOT_FOUND:
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_SYSTEM_COMMAND:
            break;
        
        default:
            break;
    }
}