#include "../../include/processes/process.h"
#include "../../include/kernel.h"

uint32_t process_id_pool = 0;

Process::Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username, uint8_t priority) :
    unique_id(process_id_pool++),
    process_state(Process_State::READY),
    kernel(kernel),
    parent_process(parent_process),
    friend_processes(friend_processes),
    waiting_for(Resource_Type::NONE),
    waiting_for_ptr(nullptr),
    username(username),
    priority(priority)
{

}

Process::~Process() {
    this -> created_resources.clear(); 
    this -> owned_resources.clear();
}

Process_State Process::execute() {
    // 4. Must return something. 
    // Usually this is virtual and implemented by children, 
    // but if not abstract, return a default state.
    return Process_State::EXECUTING; 
}

uint32_t Process::get_unique_id() {
    return this -> unique_id;
}

Process_State Process::get_process_state() {
    return this -> process_state; // 5. Added missing return
}

std::string Process::get_username() {
    return this -> username;
}

void Process::set_state(Process_State process_state) {
    this -> process_state = process_state;
}

bool Process::owns_resource(Resource_Type resource) {
    // This logic is correct
    for(const Resource* resc : this -> owned_resources) {
        if(resource == resc -> get_resource_type()) {
            return true;
        }
    }

    return false;
}

void Process::on_resource_aquired() {
    // idk if we need this
}

void Process::set_priority(uint8_t priority) {
    this -> priority = priority;
}

uint8_t Process::get_priority() const {
    return this -> priority;
}

void Process::set_waiting_resource_type(Resource_Type resource) {
    this -> waiting_for = resource;
}

void Process::set_waiting_resource(Resource* resource) {
    this -> waiting_for_ptr = resource;
}

Resource_Type Process::get_waiting_resource_type() {
    return this -> waiting_for;
}

Resource* Process::get_waiting_resource() {
    return this -> waiting_for_ptr;
}

Resource* Process::get_owned_resource(Resource_Type resource_type) {
    auto it = this -> owned_resources.begin();
    while(it != this -> owned_resources.end()) {
        if((*it) -> get_resource_type() == resource_type) {
            return (*it);
        }
    }

    return nullptr;
}

void Process::add_owned_resource(Resource* resource) {
    resource -> assign(this);
    this -> owned_resources.push_back(resource);
}


void Process::release_owned_resources() {
    for(Resource* resc : this -> owned_resources) {
        this -> kernel -> release_resource(resc -> get_resource_type());
    }

    this -> owned_resources.clear();
    
}

void Process::return_owned_resources() {
    for(Resource* resc : this -> owned_resources) {
        kernel -> return_resource_to_owner(resc);
    }

    this -> owned_resources.clear();
}

void Process::release_owned_resource(Resource_Type resource_type, std::string buffer) {
    this -> kernel -> release_resource(resource_type, buffer);

    for(auto it = this -> owned_resources.begin(); it != this -> owned_resources.end(); ++it) {
        if ((*it) -> get_resource_type() == resource_type) {
            this -> owned_resources.erase(it);
            break;
        }
    }
}

void Process::return_owned_resource(Resource_Type resource_type) {
    for(auto it = this -> owned_resources.begin(); it != this -> owned_resources.end(); ++it) {
        if ((*it) -> get_resource_type() == resource_type) {
            this -> kernel -> return_resource_to_owner((*it));
            this -> owned_resources.erase(it);
            break;
        }
    }
}

std::string Process::get_p_name() {
    return this -> name;
}

void Process::assign_vm(Virtual_Machine* vm) {

}