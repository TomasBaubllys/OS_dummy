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
