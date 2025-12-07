#include "../include/kernel.h"
#include "../include/processes/process.h"
#include "../include/processes/job_governor_process.h" // Assuming this exists based on forward decl
#include "../include/processes/start_stop_process.h"
#include "../include/io.h"
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>

Kernel::Kernel(Real_Machine* real_machine) : real_machine(real_machine) {
    init_real_machine(real_machine);
    this -> current_console_holder = nullptr;

    Process* start_stop = new Start_Stop_Process(this, nullptr, {}, SYSTEM_USERNAME);
    start_stop -> set_state(Process_State::READY);

    this -> all_processes.push_back(start_stop);
    this -> ready_queue.push(start_stop);
}

void Kernel::request_resource(Process* process, Resource_Type resource_type) {
    if (!process) return;

    process -> set_waiting_resource_type(resource_type);
    process -> set_waiting_resource(nullptr);
    process -> set_state(Process_State::BLOCKED);
}

void Kernel::release_resource(Resource_Type resource_type, std::string updated_buffer) {
    Resource* res = this -> get_resource_by_type(resource_type);

    // std::cout << (int)resource_type << std::endl;

    if (!res) return;

    res -> free_resource();
    res -> set_buffer(updated_buffer);

    std::vector<Process*> temp_container;
    bool found = false;

    while (!this -> blocked_queue.empty()) {
        Process* proc = this -> blocked_queue.top();
        this -> blocked_queue.pop();

        if(proc -> get_p_name() == MAIN_PROCESS_NAME && resource_type == Resource_Type::PIE_IN_THE_OVEN) {
            proc -> add_owned_resource(res);
            found = true;
        }

        if (!found && proc -> get_waiting_resource_type() == resource_type) {
            // std::cout << "Resource " << (int)resource_type << " FOUND for " << proc -> get_p_name() << std::endl;
            // std::cout << "given to process: " << proc->get_unique_id() << std::endl;
            proc -> add_owned_resource(res);
            
            proc -> set_state(Process_State::READY);
            proc -> set_waiting_resource_type(Resource_Type::NONE); // Clear wait reason

            this -> ready_queue.push(proc);
            found = true;
        } 
        else {
            temp_container.push_back(proc);
        }
    }

    for (Process* p : temp_container) {
        this -> blocked_queue.push(p);
    }
}


Resource* Kernel::get_resource(Process* process, Resource_Type resource_type) {
    Resource* res = this -> get_resource_by_type(resource_type);

    if (res && res -> is_free()) {
        res -> assign(process);
        return res;
    }
    return nullptr;
}

Resource* Kernel::get_resource_by_type(Resource_Type resource_type) {
    for (Resource* res : this -> resources) {
        if (res -> get_resource_type() == resource_type) {
            return res;
        }
    }
    return nullptr;
}

uint32_t Kernel::init_resource(Resource_Type resource_type, Process* owner) {
    // Using resources.size() as a simple unique ID generator since resource_id_pool isn't in header
    uint32_t new_id = (uint32_t)this -> resources.size(); 
    Resource* new_resc = new Resource(new_id, resource_type, owner);
    this -> resources.push_back(new_resc);
    return new_resc -> get_uid();
}

void Kernel::request_resource(Process* process, Resource* resource) {
    if (!process || !resource) return;

    if (resource -> is_free()) {
        process -> add_owned_resource(resource);
    }
    else {
        process -> set_waiting_resource(resource);
        process -> set_waiting_resource_type(Resource_Type::DYNAMIC);
        process -> set_state(Process_State::BLOCKED);
        // Will be pushed to blocked_queue in run() loop
    }
}

void Kernel::run() {
    while(true) {
        if(line_ready()) {
            this -> release_resource(Resource_Type::FROM_USER_INTERFACE);
        }

        if(this -> ready_queue.empty()) {
            // no more processes, shutdown...
            break;
        }

        Process* curr_p = this -> ready_queue.top();
        this -> print_running_proc(curr_p);
        this -> ready_queue.pop();
        
        curr_p -> set_state(Process_State::EXECUTING);
        
        Process_State result = curr_p -> execute();
        
        switch(result) {
            case Process_State::READY:
                this -> ready_queue.push(curr_p);
                break;
                
            case Process_State::BLOCKED: {
                bool found = false;
                for(Resource* resc : this -> resources) {
                    if(resc -> get_resource_type() == curr_p -> get_waiting_resource_type()) {
                        if(resc -> is_free()) {
                            curr_p -> add_owned_resource(resc);
                            found = true;
                        }
                    }

                }

                if(!found) {
                    this -> blocked_queue.push(curr_p); 
                }
                else {
                    this -> ready_queue.push(curr_p);
                }
                break;
            }
            case Process_State::READY_STOPPED:
                this -> ready_stopped_queue.push(curr_p);
                break;
                
            case Process_State::BLOCKED_STOPPED:
                this -> blocked_stopped_queue.push(curr_p);
                break;
                
            case Process_State::EXECUTING:
                curr_p -> set_state(Process_State::READY);
                this -> ready_queue.push(curr_p);
                break;

            default:
                break;
        }

        // to make debug easier
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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

    std::vector<Process*> kept_ready;
    while(!this -> ready_queue.empty()) {
        Process* p = this -> ready_queue.top();
        this -> ready_queue.pop();
        if(p == survivor) {
            kept_ready.push_back(p);
        }
    }
    for(Process* p : kept_ready) {
        this -> ready_queue.push(p);
    }

    while(!this -> blocked_queue.empty()) {
        this -> blocked_queue.pop();
    }

    while(!this -> ready_stopped_queue.empty()) {
        this -> ready_stopped_queue.pop();
    }

    while(!this -> blocked_stopped_queue.empty()) {
        this -> blocked_stopped_queue.pop();
    }

    this -> all_processes.erase(
        std::remove(this -> all_processes.begin(), this -> all_processes.end(), nullptr), 
        this -> all_processes.end()
    );
}

void Kernel::destroy_resources() {
    for (Resource* res : this -> resources) {
        delete res;
    }
    this -> resources.clear();
}

uint32_t Kernel::init_resource(Resource_Type resource_type, Process* owner, std::string buffer) {
    // Using resources.size() as a simple unique ID generator since resource_id_pool isn't in header
    uint32_t new_id = (uint32_t)this -> resources.size(); 
    Resource* new_resc = new Resource(new_id, resource_type);
    this -> resources.push_back(new_resc);
    return new_resc -> get_uid();
}

void release_resource_for(Resource_Type resource_type, uint32_t for_pid) {
    throw 1;
}

Hard_Disk* Kernel::get_hard_disk() {
    return &this -> real_machine -> hd;
}

CPU* Kernel::get_cpu() {
    return &this -> real_machine -> cpu;
}

Memory* Kernel::get_memory() {
    return &this -> real_machine -> mem;
}

void Kernel::release_resource_for(uint32_t resc_id, uint32_t for_pid, std::string updated_buffer) {
    // check if the resource exists... if not throw?
    Resource* resc = nullptr;
    for(auto it = this -> resources.begin(); it != this -> resources.end(); ++it) {
        if((*it) -> get_uid() == resc_id) {
            resc = (*it);
        }
    }

    // if resc not found quit lol
    if(!resc) {
        return;
    }

    // locate the process thats waiting
    for(auto it = this -> all_processes.begin(); it != this -> all_processes.end(); ++it) {
        if((*it) -> get_unique_id() == for_pid) {
            (*it) -> add_owned_resource(resc);
        }
    }
    // done ?
}

void Kernel::return_resource_to_owner(Resource* resource) {
    resource -> return_to_owner();
}

void Kernel::release_resource_for(Resource_Type resource_type, uint32_t for_pid, std::string updated_buffer) {
    // check if the resource exists... if not throw?
    Resource* resc = nullptr;
    for(auto it = this -> resources.begin(); it != this -> resources.end(); ++it) {
        if((*it) -> get_resource_type() == resource_type) {
            resc = (*it);
        } 
    }    

    // if resc not found quit lol
    if(!resc) {
        return;
    }

    // locate the process thats waiting
    for(auto it = this -> all_processes.begin(); it != this -> all_processes.end(); ++it) {
        if((*it) -> get_unique_id() == for_pid) {
            (*it) -> add_owned_resource(resc);
        }
    }
}

void Kernel::request_to_kill(uint32_t pid) {
    
}


void Kernel::assign_vm(uint32_t vm_pid, Virtual_Machine* vm) {

}

void Kernel::print_running_proc(Process* running_proc) {
    if (!running_proc) return;

    // Query terminal size
    struct winsize ws{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    int bottom = ws.ws_row;     // last row
    int col = 1;                // first column

    // Save cursor position
    printf("\x1b[s");

    // Move cursor to bottom row
    printf("\x1b[%d;%dH", bottom, col);

    // Clear that line and print status
    printf("\x1b[2K[Running: %s]", running_proc->get_p_name().c_str());

    // Restore original cursor position
    printf("\x1b[u");

    fflush(stdout);
}
