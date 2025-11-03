#ifndef RESOURCE_ELEMENT_H_INCLUDED
#define RESOURCE_ELEMENT_H_INCLUDED

#include "process.h"

typedef struct Element_List Element_List;

typedef struct Resource_Element {
    int8_t returnable;
    Process* sender;
    Process* receiver;
    Element_List* friend_list;
} Resource_Element;


#endif // RESOURCE_ELEMENT_H_INCLUDED
