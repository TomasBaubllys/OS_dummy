#include "../../include/processes/interrupt_process.h"
#include "../../include/kernel.h"
#include <sstream>

#include <iostream>

Interrupt_Process::Interrupt_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::INTERRUPT_PRIORITY){
    this -> saved_registers = {};
    this -> name = INTERRUPT_NAME;
    this -> step = Interrupt_Process_Steps::INTERRUPT_PROCESS_BLOCKED_WAITING_FOR_INTERRUPT_RESOURCE;
}

Interrupt_Process::~Interrupt_Process(){

}

// NEED A WAY TO TRACK WHICH JOB GOVERNOR IS CURRENTLY INTWRRRUPTING!
Process_State Interrupt_Process::execute(){
    switch (this -> step){
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_BLOCKED_WAITING_FOR_INTERRUPT_RESOURCE:
            if(this -> owns_resource(Resource_Type::INTERRUPT)) {
                Resource* resc = this -> get_owned_resource(Resource_Type::INTERRUPT);
                std::stringstream ss(resc -> get_buffer());
                ss >> this -> u_id_buffer;

                this -> step = Interrupt_Process_Steps::INTERRUPT_PROCESS_IDENTIFY_INTERRUPT;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::INTERRUPT);
            return Process_State::BLOCKED;
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_IDENTIFY_INTERRUPT:
			this -> kernel -> get_cpu() -> si = 0;
            this -> kernel -> get_cpu() -> pi = 0;

            this -> step = Interrupt_Process_Steps::INTERRUPT_PROCESS_RECOGNIZE_JOB_GOVERNOR_RESPONSIBLE_FOR_INTERRUPT;
            return Process_State::READY;
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_RECOGNIZE_JOB_GOVERNOR_RESPONSIBLE_FOR_INTERRUPT:
            // we already have the ID from the first step, this is not needed
            this -> step = Interrupt_Process_Steps::INTERRUPT_PROCESS_FREE_FROM_INTERRUPT_RESOURCE;
            return Process_State::READY;
        case Interrupt_Process_Steps::INTERRUPT_PROCESS_FREE_FROM_INTERRUPT_RESOURCE:
            this -> kernel -> init_resource(Resource_Type::FROM_INTERRUPT, this);
            this -> kernel -> release_resource_for(Resource_Type::FROM_INTERRUPT, this -> u_id_buffer);
            this -> return_owned_resource(Resource_Type::INTERRUPT);

            this -> step = Interrupt_Process_Steps::INTERRUPT_PROCESS_BLOCKED_WAITING_FOR_INTERRUPT_RESOURCE;
            return Process_State::READY;
        default:
            break;
    }

    return Process_State::BLOCKED_STOPPED;
}
