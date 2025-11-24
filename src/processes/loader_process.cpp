#include "../../include/processes/loader_process.h"

Loader_Process::Loader_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::LOADER_PRIORITY){

}

Loader_Process::~Loader_Process(){

}

Process_State Loader_Process::execute(){
    switch (this -> step){
        case Loader_Process_Steps::LOADER_PROCESS_BLOCKED_WAITING_FOR_LOADER_PACKAGE_RESOURCE:
            break;
        case Loader_Process_Steps::LOADER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE:
            break;
        case Loader_Process_Steps::LOADER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG:
            break;
        case Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_CHANNEL_DEVICE:
            break;
        case Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_SUPERVISOR_MEMORY:
            break;
        case Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_FROM_LOADER_FOR_JOB_GOVERNER:
            break;

        default:
            break;
    }
}