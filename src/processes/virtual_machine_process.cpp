#include "../../include/processes/virtual_machine_process.h"
#include "../../include/kernel.h"
#include <iostream>

Virtual_Machine_Process::Virtual_Machine_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::VM_PRIORITY) {
    this -> saved_registers = {};
    this -> name = VIRTUAL_MACHINE_NAME;
    this -> name += std::to_string(this -> unique_id);
    this -> step = Virtual_Machine_Steps::VIRTUAL_MACHINE_SWITCH_PROCESSOR_TO_USER_MODE;
}

Virtual_Machine_Process::~Virtual_Machine_Process(){
    destroy_virtual_machine(this -> vm);
    free(this -> vm);
}

Process_State Virtual_Machine_Process::execute(){
    switch (this -> step){
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_SWITCH_PROCESSOR_TO_USER_MODE: {
            //std::cout << "vm here" << std::endl;
            /**
             *  Move restoring registers to main loop
             * 
             */

            CPU* cpu = this -> kernel -> get_cpu();
            cpu -> mr = CPU_USER_MODE;
            this -> saved_registers = cpu_save_regs(cpu);
            // this -> saved_registers.si = 0;
            this -> step = Virtual_Machine_Steps::VIRTUAL_MACHINE_EXECUTE_USER_PROGRAM;
            return Process_State::READY;
        }
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_EXECUTE_USER_PROGRAM:
            cpu_load_regs(this -> kernel -> get_cpu(), this -> saved_registers);

            // std::cout << (int)this -> kernel -> get_cpu() -> si << " <--- sI " << std::endl;
            virtual_machine_execute(this -> vm);
            // std::cout << (int)this -> kernel -> get_cpu() -> si << " <--- sI " << std::endl;

            this -> saved_registers = cpu_save_regs(this -> kernel -> get_cpu());
            if(this -> vm -> cpu -> si + this -> vm -> cpu -> pi > 0 || this -> vm -> cpu -> ti == 0) {
                this -> step = VIRTUAL_MACHINE_FREE_RESOURCE_INTERRUPT;
            }

            return Process_State::READY;
        case Virtual_Machine_Steps::VIRTUAL_MACHINE_FREE_RESOURCE_INTERRUPT:
            // release the resource with jg id in the buffer
            this -> kernel -> release_resource(Resource_Type::INTERRUPT, std::to_string(this -> parent_process -> get_unique_id()));
            this -> step =  Virtual_Machine_Steps::VIRTUAL_MACHINE_EXECUTE_USER_PROGRAM;   
            return Process_State::READY_STOPPED;
        default:
            //std::cout << "hehe i com ehere" << std::endl;
            break;
    }

    return Process_State::BLOCKED_STOPPED;
}

void Virtual_Machine_Process::assign_vm(Virtual_Machine* vm) {
    if(!vm) {
        return;
    }

    this -> vm = vm;
}