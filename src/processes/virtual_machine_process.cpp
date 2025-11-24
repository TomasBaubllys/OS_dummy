#include "../../include/processes/virtual_machine_process.h"
#include "../../include/virtual_machine.h"

Virtual_Machine_Process::Virtual_Machine_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::VM_PRIORITY) {
    this -> saved_registers = {};
}

Virtual_Machine_Process::~Virtual_Machine_Process(){
    init_virtual_machine(this -> vm, this -> kernel -> get_cpu(), nullptr);
}

Process_State Virtual_Machine_Process::execute(){
    switch (this -> step){
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_SWITCH_PROCESSOR_TO_USER_MODE:
            break;
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_EXECUTE_USER_PROGRAM:
            cpu_load_regs(this -> kernel -> get_cpu(), this -> saved_registers);
            
            virtual_machine_excecute(this -> vm);

            this -> saved_registers = cpu_save_regs(this -> kernel -> get_cpu());

            break;
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_FREE_RESOURCE_INTERRUPT:
            break;
        
        default:
            break;
    }
}