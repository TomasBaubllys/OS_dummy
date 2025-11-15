#include "../include/resource.h"

Resource::Resource(uint32_t unique_id, Resource_Type type, Process* creator, Kernel* kernel, std::vector<Resource*> all_resources) : 
    unique_id(unique_id),
    resource_type(type),
    kernel(kernel),
    all_resources(all_resources)
{

}

Resource_Type Resource::get_resource_type() const {
    return this -> resource_type;
}