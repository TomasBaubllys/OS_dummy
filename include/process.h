#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include "saved_registers.h"
#include "kernel.h"
#include "cpu.h"

#define PROCESS_MAX_USERNAME 255

typedef struct Process_List;

typedef enum Process_State {
    EXECUTING,
    READY,
    BLOCKED,
    BLOCKED_STOPPED,
    READY,
    READY_STOPPED
} Process_State;

typedef struct Process {
    Saved_Registers saved_registers;
    uint32_t unique_id;
    Kernel* kernel;
    CPU* cpu;
    struct Process* parent_process;
    uint8_t priority;
    struct Process_List* children_process;
    struct Process_List* friend_process;
    Resource_List* owned_resources;
    Resource_List* created_resources;
    const char* username[PROCESS_MAX_USERNAME];
} Process;







#endif // PROCESS_H_INCLUDED