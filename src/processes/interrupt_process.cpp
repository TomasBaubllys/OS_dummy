#include "../../include/processes/interrupt_process.h"

Interrupt_Process::Interrupt_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::INTERRUPT_PRIORITY){
    this -> saved_registers = {};
}

Interrupt_Process::~Interrupt_Process(){

}

// NEED A WAY TO TRACK WHICH JOB GOVERNOR IS CURRENTLY INTWRRRUPTING!
Process_State Interrupt_Process::execute(){
    switch (this -> step){
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_BLOCKED_WAITING_FOR_INTERRUPT_RESOURCE:
            if(this -> owns_resource(Resource_Type::INTERRUPT)) {
                this -> step = Interrupt_Process_Steps::INTERRUPT_PROCESS_IDENTIFY_INTERRUPT;
                return Process_State::READY;
            }
            return Process_State::BLOCKED;
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_IDENTIFY_INTERRUPT:
            break;
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_RECOGNIZE_JOB_GOVERNOR_RESPONSIBLE_FOR_INTERRUPT:
            break;
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_FREE_FROM_INTERRUPT_RESOURCE:
            break;
        
        default:
            break;
    }
}