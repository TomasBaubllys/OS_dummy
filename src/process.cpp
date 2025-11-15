#include "../include/process.h"

Process::Process(Saved_Registers saved_registers, uint32_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) :
    saved_registers(saved_registers),
    unique_id(unique_id),
    current_step(0),
    process_state(process_state),
    kernel(kernel),
    cpu(cpu),
    parent_process(parent_process),
    children_processes(children_processes),
    friend_processes(friend_processes),
    owned_resources(owned_resources),
    created_resources(created_resources),
    needed_resources(needed_resources),
    username(username)
{

}

Process::~Process() {

}

int8_t Process::execute() {

}

uint32_t Process::get_unique_id() {
    return this -> unique_id;
}

uint8_t Process::get_current_step() {
    return this -> current_step; 
}

Process_State Process::get_process_state() {
    this -> process_state;
}

std::string Process::get_username() {
    return this -> username;
}

void Process::set_state(Process_State process_state) {
    this -> process_state = process_state;
}

bool Process::owns_resource(Resource_Type resource) {
    for(const Resource* resc : this -> owned_resources) {
        if(resource == resc -> get_resource_type()) {
            return true;
        }
    }

    return false;
}
