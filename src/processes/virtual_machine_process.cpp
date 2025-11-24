#include "../../include/processes/virtual_machine_process.h"

Virtual_Machine_Process::Virtual_Machine_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::VM_PRIORITY) {
    this -> saved_registers = {};
}

Virtual_Machine_Process::~Virtual_Machine_Process(){

}

Process_State Virtual_Machine_Process::execute(){
    switch (this -> step){
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