#include "../include/virtual_machine_process.h"

Virtual_Machine_Process::Virtual_Machine_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username){

}

Virtual_Machine_Process::~Virtual_Machine_Process(){

}

int8_t Virtual_Machine_Process::execute(){
    switch (this -> current_step){
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_SWITCH_PROCESSOR_TO_USER_MODE:
            break;
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_EXECUTE_USER_PROGRAM:
            break;
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_FREE_RESOURCE_INTERRUPT:
            break;
        
        default:
            break;
    }
}