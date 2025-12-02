#include "../../include/processes/job_governor_process.h"
#include "../../include/virtual_machine.h"
#include "../../include/kernel.h"
#include <sstream>

/**
 * 
 * 
 * 
 * 
 * 
 *  call the interrupt here, just lock the resources.... GEDA/PUTA etc... -> interrupt(this -> kernel -> cpu) 
 */

Job_Governor_Process::Job_Governor_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username): 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::JOB_GOVERNOR_PRIORITY){

}

Job_Governor_Process::~Job_Governor_Process(){

}

Process_State Job_Governor_Process::execute(){
    switch (this -> step){
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_MEMORY_RESOURCE:
            if(this -> owns_resource(Resource_Type::USER_MEMORY)) {
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::USER_MEMORY);
            return Process_State::BLOCKED;
        /* NO NEED FOR THIS SINCE WE DONT DIFERENTIATE BETWEEN THIS AND THE FIRST STEP case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_MEMORY_FOR_PAGING_TABLE: 
            if(this -> owns_resource(Resource_Type::USER_MEMORY)) {

            }    

            this -> kernel -> request_resource();
            ;*/
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_VIRTUAL_MACHINE: 
            // create the virtual machine
            static Virtual_Machine* vm = (Virtual_Machine*)malloc(sizeof(Virtual_Machine));
            init_virtual_machine(vm, this -> kernel -> get_cpu(), this -> kernel -> get_memory());
            this -> saved_registers.ptr = this -> kernel -> get_cpu() -> ptr;

            return Process_State::READY;    
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_LOADER_PACKAGE_RESOURCE: {
            std::stringstream ss;
            // program length is always the length of the supervisor memory size
            ss << this -> unique_id  << MEM_SUPERVISOR_MEMORY_SIZE * MEM_WORD_SIZE << " " << this -> saved_registers.ptr;
            // this is not good, we must release the resources in some dynamic way... or maybe not???
            this -> kernel -> release_resource(Resource_Type::LOADER_PACKAGE, ss.str());
            return Process_State::READY;
        }
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FROM_LOADER_RESOURCE:
            if(this -> owns_resource(Resource_Type::FROM_LOADER)) {
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::FROM_LOADER);
            return Process_State::BLOCKED;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CREATE_PROCESS_VIRTUAL_MACHINE:
            /*
                CREATE THE ACTUAL VM PROCESS AND ADD THE VM TO IT
            */   
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_FROM_INTERRUPT_RESOURCE:
            if(this -> owns_resource(Resource_Type::FROM_INTERRUPT)) {
                // not really stop, identify the interupts
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_STOP_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::FROM_INTERRUPT);
            return Process_State::BLOCKED;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_STOP_PROCESS_VIRTUAL_MACHINE: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_IO_INTERRUPT:
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_IO_REACHED_LIMIT: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_REACHED_LIMIT: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_GEDA_INTERRUPT: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_BLOCKED_WAITING_FOR_USER_INPUT_RESOURCE: 
            if(this -> owns_resource(Resource_Type::USER_INPUT)) {
                this -> step = Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::USER_INPUT);
            return Process_State::BLOCKED;
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_ACTIVATE_PROCESS_VIRTUAL_MACHINE: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_BP_BG_INTERRUPT: 
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
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_CHECK_PSTR_PUTA_INTERRUPT: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_STRING_IN_MEMORY_RESOURCE_WITH_INFO_OUTPUT_CONTENT:
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_REMOVE_PROCESS_VIRTUAL_MACHINE: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_USER_MEMORY_RESOURCE: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_PIE_IN_THE_OVEN_RESOURCE: 
            break;
        case Job_Governor_Process_Steps::JOB_GOVERNOR_PROCESS_FREE_SYSTEM_COMMAND_RESOURCE: 
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