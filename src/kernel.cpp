#include "../include/kernel.h"
#include "../../include/processes/process.h"
#include "../../include/processes/start_stop_process.h"
#include "../include/io.h"
#include <algorithm>

struct Kernel::Process_Comparator {
    bool operator()(const Process* a, const Process* b) const {
        return a -> get_priority() < b -> get_priority();
    }
};

Kernel::Kernel(Real_Machine* real_machine) : real_machine(real_machine) {
    // create a process start_stop
    Process* start_stop = new Start_Stop_Process(this, nullptr, {}, SYSTEM_USERNAME);
    start_stop -> set_state(Process_State::READY);

    this -> all_processes.push_back(start_stop);

    this -> ready_queue.push(start_stop);
}

void Kernel::request_resource(Process* process, Resource_Type resource_type) {
    Resource* resource = this -> resources[resource_type];

    // try again later...
    if(resource == nullptr) {
        return;
    }

    if(resource -> is_free()) {
        resource -> assign(process);
        process -> on_resource_aquired();
        this -> ready_queue.push(process);
    }
    else {
        resource -> enqueue(process);
        process -> set_state(Process_State::BLOCKED);
    }
}

Resource* Kernel::get_resource(Resource_Type resource_type) {
    auto it = this -> resources.find(resource_type);
    if(it == this -> resources.end()) {
        return nullptr;
    }

    return it -> second;
}

void Kernel::init_resource(Resource_Type resource_type) {
    if(this -> resources.find(resource_type) != this -> resources.end()) {
        return;
    }

    this -> resources[resource_type] = new Resource(resource_id_pool++, resource_type);
}

void release_resource(Process* process, Resource_Type resource_type) {

}

void Kernel::run() {
    while(true) {
        if(line_ready()) {
            this -> init_resource(Resource_Type::FROM_USER_INTERFACE);
        }

        if(this -> ready_queue.empty()) {
            // should never be empty...
            exit(-1);
        }

        Process* curr_p = this -> ready_queue.top();
        this -> ready_queue.pop();
        curr_p -> set_state(Process_State::EXECUTING);
        
        Process_State result = curr_p -> execute();

        switch(result) {
            case Process_State::READY: {

            }
            case Process_State::BLOCKED: {

            }
            // etc...
            default: {
                break;
                
            }
        }

    }
}

Channel_Device* Kernel::get_channel_device() {
    return &this -> real_machine -> ch_dev;
}

void Kernel::kill_processes_except(Process* survivor) {
    for(Process*& proc : this -> all_processes) {
        if(proc != survivor) {
            delete proc;
            proc = nullptr;     
        }
    }

    // clean ready queue (start stop shoudnt be in the queue)
    bool survivor_is_in_q = false;
    while(!this -> ready_queue.empty()) {
        Process* proc = this -> ready_queue.top();
        if(proc == survivor) {
            survivor_is_in_q = true;
        }
        this -> ready_queue.pop();
    }

    if(survivor_is_in_q) {
        this -> ready_queue.push(survivor);
    }

    this -> all_processes.erase(std::remove_if(this -> all_processes.begin(), this -> all_processes.end(),
    [survivor](Process* proc) {
        return survivor != proc;
    }), this -> all_processes.end());

}

void Kernel::destroy_resources() {
    for(std::pair<Resource_Type, Resource*> resc : this -> resources) {
        delete resc.second;
        resc.second = nullptr;
    }

    this -> resources.clear();
}