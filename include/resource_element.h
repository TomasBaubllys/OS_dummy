#ifndef RESOURCE_ELEMENT_H_INCLUDED
#define RESOURCE_ELEMENT_H_INCLUDED

#include "process.h"
#include "element_list.h"

typdef struct Resource_Element {
    int8_t return;
    Process* sender;
    Process* receiver;
    Element_List* friend_list;
} Resource_Element;


#endif // RESOURCE_ELEMENT_H_INCLUDED