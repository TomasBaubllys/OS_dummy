#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include "../saved_registers.h"
#include "../resource.h"
#include "../cpu.h"
#include <vector>
#include <string>

#define PROCESS_MAX_PRIORITY UINT8_MAX
#define PROCESS_MIN_PRIORITY 0

class Kernel;

extern uint32_t process_id_pool;

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
    JOB_CONTROL_LANGUAGE_PRIORITY = 80,
    JOB_GOVERNOR_PRIORITY = 90,
    MAIN_PROCESS_PRIORITY = 150,
    START_STOP_PRIORITY = 240,
    INTERRUPT_PRIORITY = PROCESS_MAX_PRIORITY
} Process_Priorities;

class Process {
    protected:
        Saved_Registers saved_registers;
        uint32_t unique_id;
        uint32_t u_id_buffer; // used for dynamic resources, to know to who to return the resource to
        Process_State process_state;

        uint8_t priority;

        Kernel* kernel;
        Process* parent_process;

        // std::vector<Process*> children_processes;
        std::vector<Process*> friend_processes;

        std::vector<Resource*> owned_resources;
        std::vector<Resource*> created_resources;
        // for static
        Resource_Type waiting_for;
        // for dynamic
        Resource* waiting_for_ptr;

        std::string username;

    public:
        Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username, uint8_t priority);
        virtual ~Process();
        virtual Process_State execute();

        void set_state(Process_State process_state);
        uint32_t get_unique_id();
        Process_State get_process_state();
        std::string get_username();
        bool owns_resource(Resource_Type resource_type);

        void set_waiting_resource_type(Resource_Type resource_type);

        void set_waiting_resource(Resource* resource);

        void on_resource_aquired();

        void set_priority(uint8_t priority);

        uint8_t get_priority() const;

        Resource_Type get_waiting_resource_type();

        Resource* get_waiting_resource();

        Resource* get_owned_resource(Resource_Type resource_type);

        void add_owned_resource(Resource* resource);

        void free_owned_resources();
};

#endif // PROCESS_H_INCLUDED
