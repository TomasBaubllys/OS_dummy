#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include "saved_registers.h"
#include "kernel.h"
#include "cpu.h"
#include <vector>
#include <string>

#define PROCESS_MAX_USERNAME 255

//typedef struct Process_List Process_List;
//typedef struct Resource_List Resource_List;

typedef enum Process_State {
    EXECUTING,
    READY,
    BLOCKED,
    BLOCKED_STOPPED,
    READY_STOPPED
} Process_State;

class Process {
    private:
        Saved_Registers saved_registers;
        uint32_t unique_id;
        uint8_t current_step;
        Process_State process_state;

        Kernel* kernel;
        CPU* cpu;
        Process* parent_process;

        std::vector<Process*> children_processes;
            //Process_List* children_processes;
        std::vector<Process*> friend_processes;
            //Process_List* friend_processes;

        std::vector<Resource*> owned_resources;
        std::vector<Resource*> created_resources;
        std::vector<Resource*> needed_resources;
            //Resource_List* owned_resources;
            //Resource_List* created_resources;
            //Resource_List* needed_resources;

        std::string username;

    public:
        Process(Saved_Registers saved_registers, uint32_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        virtual ~Process();
        virtual int8_t execute();

        uint32_t get_unique_id();
        uint8_t get_current_step();
        Process_State get_process_state();
        std::string get_username();
};

/*
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
	// function to be called with with process
	int8_t (*execute)(struct Process* self);
} Process;

// must have all the arguments required
Process* create_process();

// deletes the process and frees the memory
int8_t destroy_process(Process* process);

void remove_from

*/




#endif // PROCESS_H_INCLUDED
