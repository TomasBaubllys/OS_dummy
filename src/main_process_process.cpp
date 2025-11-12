#include "../include/main_process_process.h"

Main_Process_Process::Main_Process_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username){

}

Main_Process_Process::~Main_Process_Process(){

}

int8_t Main_Process_Process::execute(){
    switch (this -> current_step){
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_PIE_IN_THE_OVEN_FREE:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_ITS_SHUT_DOWN:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CREATE_RESOURCE_MOS_END:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_ITS_KILL:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_REMOVE_PROCESS_JOB_GOVERNOR_1:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_NONEXISTING_SYSTEM_COMMAND:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_RUNTIME_0:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CREATE_PROCESS_JOB_OVERNOR_WITH_PIE_IN_THE_OVEN_RESOURCE:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_REMOVE_PROCESS_JOB_GOVERNER_2:
            break;
        default:
            break;
    }
}