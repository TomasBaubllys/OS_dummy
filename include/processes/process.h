#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include "saved_registers.h"
#include "resource.h"
#include "kernel.h"
#include "cpu.h"
#include <vector>
#include <string>

#define PROCESS_MAX_PRIORITY UINT8_MAX
#define PROCESS_MIN_PRIORITY 0

uint32_t process_id_pool = 0;

enum class Process_State : uint8_t {
    EXECUTING,
    READY,
    BLOCKED,
    BLOCKED_STOPPED,
    READY_STOPPED
};

typedef enum Process_Priorities : uint8_t {
    IDLE_PRIORITY = PROCESS_MIN_PRIORITY,
    VM_PRIORITY = 10,
    PRINTER_PRIORITY = 40,
    LOADER_PRIORITY = 60,
    READ_FROM_INTERFACE_PRIORITY = 70,
    JOB_GOVERNOR_PRIORITY = 90,
    MAIN_PROCESS_PRIORITY = 150,
    START_STOP_PRIORITY = 240,
    INTERRUPT_PRIORITY = PROCESS_MAX_PRIORITY
} Process_Priorities;

class Process {
    protected:
        Saved_Registers saved_registers;
        uint32_t unique_id;
        Process_State process_state;

        uint8_t priority;

        Kernel* kernel;
        Process* parent_process;

        // std::vector<Process*> children_processes;
        std::vector<Process*> friend_processes;

        std::vector<Resource*> owned_resources;
        std::vector<Resource*> created_resources;
        Resource_Type waiting_for;

        std::string username;

    public:
        Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username, uint8_t priority);
        virtual ~Process();
        virtual Process_State execute();

        void set_state(Process_State process_state);
        uint32_t get_unique_id();
        Process_State get_process_state();
        std::string get_username();
        bool owns_resource(Resource_Type resource);

        void on_resource_aquired();

        void set_priority(uint8_t priority);

        uint8_t get_priority() const;
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
