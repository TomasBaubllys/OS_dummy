#include "../../include/processes/process.h"

Process::Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username, uint8_t priority) :
    unique_id(process_id_pool++),
    process_state(process_state),
    kernel(kernel),
    parent_process(parent_process),
    friend_processes(friend_processes),
    owned_resources(owned_resources),
    created_resources(created_resources),
    waiting_for(Resource_Type::NONE),
    username(username),
    priority(priority)
{

}

Process::~Process() {
    // destroy all owned resources
    for(Resource* resc : this -> created_resources) {
        delete resc;
        resc = nullptr;
    }

    this -> created_resources.clear();
}

Process_State Process::execute() {

}

uint32_t Process::get_unique_id() {
    return this -> unique_id;
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

void Process::on_resource_aquired() {

}

void Process::set_priority(uint8_t priority) {
    this -> priority = priority;
}

uint8_t Process::get_priority() const {
    return this -> priority;
}

