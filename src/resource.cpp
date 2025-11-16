#include "../include/resource.h"

Resource::Resource(uint32_t unique_id, Resource_Type type, Process* owner) :
    unique_id(unique_id),
    resource_type(type),
    owner(owner)
{

}

Resource_Type Resource::get_resource_type() const {
    return this -> resource_type;
}

void Resource::enqueue(Process* process) {
    this -> waiting.push(process);
}

bool Resource::is_free() {
    return this -> owner == nullptr;
}

void Resource::free_resource() {
    this -> owner = nullptr;
}

void Resource::assign(Process* process) {
    this -> owner = process;
}

Process* Resource::next_waiting() {
    if(this -> waiting.empty()) {
        return nullptr;
    }

    Process* process = this -> waiting.front();
    this -> waiting.pop();

    return process;
}