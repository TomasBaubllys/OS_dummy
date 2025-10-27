#ifndef RESOURCE_LIST_H_INCLUDED
#define RESOURCE_LIST_H_INCLUDED

#include "resource.h"

typdef struct Resource_List {
    Resource* resource_list;
    uint32_t size;
    Kernel* kernel;
} Resource_List;



#endif // RESOURCE_LIST_H_INCLUDED