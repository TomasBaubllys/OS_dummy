#include "../../include/processes/job_control_language_process.h"

Job_Control_Language_Process::Job_Control_Language_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::JOB_CONTROL_LANGUAGE_PRIORITY){

} 

Job_Control_Language_Process::~Job_Control_Language_Process(){

}

Process_State Job_Control_Language_Process::execute(){
    switch (this -> step){
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_BLOCKED_WAIT_FOR_TASK_IN_SUPERVISOR:
            if(this -> owns_resource(Resource_Type::TASK_IN_SUPERVISOR)) {
                this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_INITIALIZE_PROGRAM_LIST;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::TASK_IN_SUPERVISOR);
            return Process_State::BLOCKED;
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