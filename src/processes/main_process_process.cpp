#include "../../include/processes/main_process_process.h"

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
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CHECK_IF_ITS_SHUT_DOWN:
            break;
        case Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_CREATE_RESOURCE_MOS_END:
            this -> kernel -> init_resource(Resource_Type::MOS_END);
            this -> step = Main_Process_Process_Steps::MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND;
            return Process_State::READY;
            
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