#include "../../include/processes/interrupt_process.h"

Interrupt_Process::Interrupt_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::INTERRUPT_PRIORITY){
    this -> saved_registers = {};
}

Interrupt_Process::~Interrupt_Process(){

}

Process_State Interrupt_Process::execute(){
    switch (this -> current_step){
        case Interrupt_Process_Steps::INTERRUPT_RPOCESS_BLOCKED_WAITING_FOR_INTERRUPT_RESOURCE:
            break;
        case Interrupt_Process_Steps::INTERRUPT_RPOCESS_IDENTIFY_INTERRUPT:
            break;
        case Interrupt_Process_Steps::INTERRUPT_RPOCESS_RECOGNIZE_JOB_GOVERNOR_RESPONSIBLE_FOR_INTERRUPT:
            break;
        case Interrupt_Process_Steps::INTERRUPT_RPOCESS_FREE_FROM_INTERRUPT_RESOURCE:
            break;
        
        default:
            break;
    }
}