#ifndef ELEMENT_LIST_H_INCLUDED
#define ELEMENT_LIST_H_INCLUDED

#include "resource_element.h"
#include "resource.h"

typedef struct Element_List{
    Resource_Element* element_list;
    uint32_t size;
    Resource* owner_resource;
} Element_List;


#endif // ELEMENT_LIST_H_INCLUDED