#include "../include/loader_process.h"

Loader_Process::Loader_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username){

}

Loader_Process::~Loader_Process(){

}

int8_t Loader_Process::execute(){
    switch (this -> curent_step)
    {
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