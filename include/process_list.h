#ifndef PROCESS_LIST_H_INCLUDED
#define PROCESS_LIST_H_INCLUDED

#include "process.h"

typdef struct Process_List{
    Kernel* kernel;
    Process* process_list;
    uint32_t size;
    uint32_t capacity;
}




#endif // PROCESS_LIST_H_INCLUDED