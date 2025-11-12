#include "../include/interrupt_process.h"

Interrupt_Process::Interrupt_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username){

}

Interrupt_Process::~Interrupt_Process(){

}

int8_t Interrupt_Process::execute(){
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