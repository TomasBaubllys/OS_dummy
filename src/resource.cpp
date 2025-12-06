#include "../include/resource.h"
#include "../include/processes/process.h"

Resource::Resource(uint32_t unique_id, Resource_Type type, Process* owner) :
    unique_id(unique_id),
    resource_type(type),
    owner(owner),
    user(owner) // by default the owner is the user, so the resource is not released!
{

}

Resource_Type Resource::get_resource_type() const {
    return this -> resource_type;
}

bool Resource::is_free() {
    return this -> user == nullptr;
}

void Resource::free_resource() {
    this -> user = nullptr;
}

void Resource::assign(Process* process) {
    this -> user = process;
}

std::string Resource::get_buffer() {
    return this -> buffer;
}

size_t Resource::get_buffer_size() {
    return this -> buffer.size();
}

void Resource::set_buffer(std::string buffer) {
    this -> buffer = buffer;
}

bool Resource::is_dedicated() {
    return this -> dedicated_to == 0;
}

uint32_t Resource::get_dedicated() {
    return this -> dedicated_to;
}

void Resource::set_dedicated(uint32_t pid) {
    this -> dedicated_to = pid;
}

uint32_t Resource::get_owner_id() {
    return this -> owner -> get_unique_id();
}

uint32_t Resource::get_uid() {
    return this -> unique_id;
}

void Resource::return_to_owner() {
    this -> user = this -> owner;
}