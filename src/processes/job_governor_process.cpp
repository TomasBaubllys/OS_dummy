#include "../../include/processes/job_governor_process.h"
#include "../../include/virtual_machine.h"
#include "../../include/kernel.h"
#include "../../include/processes/virtual_machine_process.h"
#include <cstdint>
#include <sstream>
#include <iostream>
#include <string>

Job_Governor_Process::Job_Governor_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username):
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::JOB_GOVERNOR_PRIORITY){
    this -> name = JG_NAME;
    this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_MEMORY_RESOURCE;
    //std::cout << "Dobze dobze..." << std::endl;
    io_interrupt = false;
    std::cout << JB_CREATION_MSG << this -> unique_id << std::endl;
}

Job_Governor_Process::~Job_Governor_Process(){
	this -> kernel -> request_to_kill(this -> u_id_buffer);
}

Process_State Job_Governor_Process::execute(){
    //std::cout << "JOB_GOVERNOR::ID: " << this -> u_id_buffer << "Step: " << (uint16_t)this -> step << std::endl;
    switch (this -> step){
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_MEMORY_RESOURCE:
            if(this -> owns_resource(Resource_Type::USER_MEMORY)) {
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::USER_MEMORY);
            return Process_State::BLOCKED;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_VIRTUAL_MACHINE:
            // create the virtual machine
            this -> _vm_holder = (Virtual_Machine*)malloc(sizeof(Virtual_Machine));
            init_virtual_machine(this -> _vm_holder, this -> kernel -> get_cpu(), this -> kernel -> get_memory());
            this -> saved_registers.ptr = this -> kernel -> get_cpu() -> ptr;
            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_LOADER_PACKAGE_RESOURCE;
            return Process_State::READY;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_LOADER_PACKAGE_RESOURCE: {
            std::stringstream ss;
            // program length is always the length of the supervisor memory size
            ss << this -> unique_id  << " " << MEM_SUPERVISOR_MEMORY_SIZE * MEM_WORD_SIZE << " " << this -> saved_registers.ptr;
            // this is not good, we must release the resources in some dynamic way... or maybe not???
            this -> kernel -> release_resource(Resource_Type::LOADER_PACKAGE, ss.str());
            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FROM_LOADER_RESOURCE;
            return Process_State::READY;
        }
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FROM_LOADER_RESOURCE:
            if(this -> owns_resource(Resource_Type::FROM_LOADER)) {
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::FROM_LOADER);
            return Process_State::BLOCKED;


        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_PROCESS_VIRTUAL_MACHINE: {
            this -> u_id_buffer =  this -> kernel -> create_process<Virtual_Machine_Process>(this, {},  SYSTEM_USERNAME);
            //std::cout << "vm_pid " << this -> u_id_buffer << std::endl;
            this -> kernel -> assign_vm(this -> u_id_buffer, this -> _vm_holder);

            Process* proc = this -> kernel -> get_proc_by_id(this -> u_id_buffer);
            Saved_Registers& vm_regs = proc -> ref_sregs();
            vm_regs.ptr = this -> saved_registers.ptr;

            // this -> release_owned_resource(Resource_Type::USER_MEMORY);
            // delete from loader???

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_FROM_INTERRUPT_RESOURCE;
            return Process_State::READY;
            /*
                CREATE THE ACTUAL VM PROCESS AND ADD THE VM TO IT
            */
        }
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_FROM_INTERRUPT_RESOURCE:
            //std::cout << "blocked again" << std::endl;
            if(this -> owns_resource(Resource_Type::FROM_INTERRUPT)) {
                // not really stop, identify the interupts
                            //std::cout << "blocked again inside" << std::endl;

                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_STOP_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::FROM_INTERRUPT);
            return Process_State::BLOCKED;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_STOP_PROCESS_VIRTUAL_MACHINE:
            //this -> kernel -> request_to_kill(vm_pid);
            // ??
            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_IO_INTERRUPT;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_IO_INTERRUPT: {
            Process* vm_p = this -> kernel -> get_proc_by_id(this -> u_id_buffer);
            Saved_Registers& vm_regs = vm_p -> ref_sregs();
            cpu_load_regs(this -> kernel -> get_cpu(), vm_regs);


            io_interrupt = false;

//            switch(this -> kernel -> get_cpu() -> si){
            switch(vm_regs.si){

                case Cpu_Si_Type::CPU_SI_GEDA: {
                    this -> kernel -> console_holder_q.push(this);
                    this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_INPUT_RESOURCE;
                    this -> kernel -> get_cpu() -> si = 0;
                    vm_regs.si = 0;
                    return Process_State::READY;
                }
                case Cpu_Si_Type::CPU_SI_BG:
                case Cpu_Si_Type::CPU_SI_BP:
                case Cpu_Si_Type::CPU_SI_PSTR:
                case Cpu_Si_Type::CPU_SI_PUTA:
                    io_interrupt = true;
                    break;
                default:
                    break;
            }

            if(io_interrupt){
                //std::cout << "io " << std::endl;
                Saved_Registers cpu_save = cpu_save_regs(this -> kernel -> get_cpu());
                this -> kernel -> get_cpu() -> si = vm_regs.si;
                cpu_load_regs(this -> kernel -> get_cpu(), vm_regs);
                interrupt(this -> kernel -> get_cpu());
                cpu_load_regs(this -> kernel -> get_cpu(), cpu_save);
                vm_regs.si = 0;
                this -> kernel -> get_cpu() -> si = 0;
                this -> kernel -> get_cpu() -> pi = 0;
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }
//            else if(this -> kernel -> get_cpu() -> si + this -> kernel -> get_cpu() -> pi > 0){
            else if(vm_regs.pi + vm_regs.si > 0 && vm_regs.pi != 2){

                // std::cout << "SI: " << this -> kernel -> get_cpu() -> si << std::endl;
                // std::cout << "PI: " << vm_regs.pi << " VM ID = " << this -> u_id_buffer << std::endl;
                // std::cout << "TI: " << (int)this -> kernel -> get_cpu() -> ti << std::endl;

                // std::cout << "not io " << std::endl;
                // this -> kernel -> get_cpu() -> si = 0;
                // this -> kernel -> get_cpu() -> pi = 0;
                vm_regs.pi = 0;
                vm_regs.si = 0;
                // std::cout << "KILLED" << std::endl;
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_REMOVE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }
            else if(vm_regs.ti == 0){
                // this -> kernel -> lower_priority(this -> u_id_buffer);
                this -> kernel -> get_cpu() -> ti = CPU_DEFAULT_TIMER_VALUE;
                vm_regs.ti = CPU_DEFAULT_TIMER_VALUE;
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }
            else{
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            break;
        }
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_IO_REACHED_LIMIT:
            // no clue :(
            static bool limit_reached;
            limit_reached = false;
            /*
            *  HERE CHECK IF IO LIMIT REACHED
            *
            *
            */
            // actual check happens here
            if(limit_reached){
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_REACHED_LIMIT;
                return Process_State::READY;
            }
            else{
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_GEDA_INTERRUPT;
                return Process_State::READY;
            }

            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_REACHED_LIMIT:
            this -> kernel -> release_resource(Resource_Type::STRING_IN_MEMORY, JOB_GOVERNOR_PROCESS_MSG_IO_LIMIT_REACHED);

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_REMOVE_PROCESS_VIRTUAL_MACHINE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_GEDA_INTERRUPT:
            if(this -> kernel -> get_cpu() -> si == Cpu_Si_Type::CPU_SI_GEDA){
                interrupt(this -> kernel -> get_cpu());
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_INPUT_RESOURCE;
                return Process_State::READY;
            }
            else{
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_BP_BG_INTERRUPT;
                return  Process_State::READY;
            }
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_INPUT_RESOURCE:
            if(this -> owns_resource(Resource_Type::USER_INPUT)) {
                Resource* resc = this -> get_owned_resource(Resource_Type::USER_INPUT);
                Process* vm_p = this -> kernel -> get_proc_by_id(this -> u_id_buffer);
                Saved_Registers& vm_regs = vm_p -> ref_sregs();
                vm_regs.si = 0;
                try {
                    vm_regs.ra = stoi(resc -> get_buffer());
                }
                catch(...) {
                    vm_regs.ra = resc -> get_buffer().at(0);
                }
                this -> return_owned_resource(Resource_Type::USER_INPUT);

                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::USER_INPUT);
            return Process_State::BLOCKED;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE:
            // make vm process the middle step
            this -> kernel -> unstop_ready(this -> u_id_buffer);

            io_interrupt = false;

            //std::cout << "miau" << std::endl;

            this -> return_owned_resource(Resource_Type::FROM_INTERRUPT);


            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_FROM_INTERRUPT_RESOURCE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_BP_BG_INTERRUPT:

            if(this -> kernel -> get_cpu() -> si == Cpu_Si_Type::CPU_SI_BP || this -> kernel -> get_cpu() -> si == Cpu_Si_Type::CPU_SI_BG){
                interrupt(this -> kernel -> get_cpu());

                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE;
                return Process_State::READY;
            }
            else{
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_PSTR_PUTA_INTERRUPT;
                return  Process_State::READY;
            }
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE:
            if(this -> owns_resource(Resource_Type::CHANNEL_DEVICE)) {
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::CHANNEL_DEVICE);
            return Process_State::BLOCKED;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG:
            interrupt(this -> kernel -> get_cpu());

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE:
            this -> kernel -> release_resource(Resource_Type::CHANNEL_DEVICE);

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_PSTR_PUTA_INTERRUPT:
            if(this -> kernel -> get_cpu() -> si == Cpu_Si_Type::CPU_SI_PSTR || this -> kernel -> get_cpu() -> si == Cpu_Si_Type::CPU_SI_PUTA){
                interrupt(this -> kernel -> get_cpu());

                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_OUTPUT_CONTENT;
                return Process_State::READY;
            }
            else{
                // should never ever happen
                throw(3725);
            }
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_OUTPUT_CONTENT:
            //this -> kernel -> release_resource(Resource_Type::STRING_IN_MEMORY, JOB_GOVERNOR_PROCESS_MSG_PLACEHOLDER);

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE;

            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_REMOVE_PROCESS_VIRTUAL_MACHINE:
            this -> kernel -> request_to_kill(this -> u_id_buffer);

            //std::cout << "after req to kill" << std::endl;

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_USER_MEMORY_RESOURCE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_USER_MEMORY_RESOURCE:
            this -> release_owned_resource(Resource_Type::USER_MEMORY);
            // std::cout << "here" << std::endl;

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_PIE_IN_THE_OVEN_RESOURCE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_PIE_IN_THE_OVEN_RESOURCE:
            this -> kernel -> release_resource(Resource_Type::PIE_IN_THE_OVEN, std::to_string(this -> get_unique_id()));

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_SYSTEM_COMMAND_RESOURCE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_SYSTEM_COMMAND_RESOURCE:
            this -> kernel -> release_resource(Resource_Type::SYSTEM_COMMAND);

            this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_NONEXISTANT_RESOURCE;
            return Process_State::READY;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_NONEXISTANT_RESOURCE:
            if(this -> owns_resource(Resource_Type::NON_EXISTANT)) {
                return Process_State::BLOCKED_STOPPED;
            }

            this -> kernel -> request_resource(this, Resource_Type::NON_EXISTANT);
            return Process_State::BLOCKED_STOPPED;
            break;
        default:
            break;
    }

    return Process_State::BLOCKED_STOPPED;
}
