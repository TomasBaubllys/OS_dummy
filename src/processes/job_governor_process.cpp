#include "../../include/processes/job_governor_process.h"

Job_Governor_Process::Job_Governor_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username): 
    Process(kernel, parent_process, friend_processes, username){

}

Job_Governor_Process::~Job_Governor_Process(){

}

Process_State Job_Governor_Process::execute(){
    switch (this -> step)
    {
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_MEMORY_RESOURCE:
        if(this -> owns_resource(Resource_Type::USER_MEMORY)) {
            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_LOADER_PACKAGE_RESOURCE;
            return Process_State::READY;
        }

        return Process_State::BLOCKED;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_LOADER_PACKAGE_RESOURCE:
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FROM_LOADER_RESOURCE:
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_MEMORY_FOR_PAGING_TABLE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_PROCESS_VIRTUAL_MACHINE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_FROM_INTERRUPT_RESOURCE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_STOP_PROCESS_VIRTUAL_MACHINE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_IO_INTERRUPT:
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_IO_REACHED_LIMIT: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_REACHED_LIMIT: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_GEDA_INTERRUPT: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_INPUT_RESOURCE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_BP_BG_INTERRUPT: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_PSTR_PUTA_INTERRUPT: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_OUTPUT_CONTENT:
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_REMOVE_PROCESS_VIRTUAL_MACHINE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_USER_MEMORY_RESOURCE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_PIE_IN_THE_OVEN_RESOURCE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_SYSTEM_COMMAND_RESOURCE: 
        break;
    case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_NONEXISTANT_RESOURCE: 
        break;
    default:
        break;
    }
}