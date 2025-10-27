#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include "saved_registers.h"
#include "kernel.h"
#include "cpu.h"

#define PROCESS_MAX_USERNAME 255

typedef struct Process_List;
typedef struct Resource_List;

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
    Process* parent_process;
    uint8_t priority;
    Process_List* children_process;
    Process_List* friend_process;
    Resource_List* owned_resources;
    Resource_List* created_resources;
    Resource_List* needed_resources;
    const char* username[PROCESS_MAX_USERNAME];
	uint8_t current_step;
	Process_State process_state;
} Process;







#endif // PROCESS_H_INCLUDED
