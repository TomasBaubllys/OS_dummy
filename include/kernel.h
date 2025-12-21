#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <cstdint>
#include <stdint.h>
#include "real_machine.h"
#include <unordered_map>
#include <string>
#include "../include/resource.h"
#include "../include/processes/process.h"
#include "../include/processes/idle_process.h"
#include "../include/processes/interrupt_process.h"
#include "../include/processes/job_control_language_process.h"
#include "../include/processes/job_governor_process.h"
#include "../include/processes/loader_process.h"
#include "../include/processes/main_process_process.h"
#include "../include/processes/printer_process.h"
#include "../include/processes/read_from_interface_process.h"
#include "../include/processes/start_stop_process.h"
#include "../include/processes/virtual_machine_process.h"
#include <list>
#include <queue>

#define SYSTEM_USERNAME "system"
#define RMI_SHUTDOWN_COMMAND "$SHUTDOWN"
#define RMI_FILE_INPUT "F$"
#define RMI_SYS_COMMAND "$"
#define RMI_KILL_COMMAND "$KILL"
#define STR_MEM_UNKNOWN_SYS_COM_ERR_MSG "Unknown system command!\n"

#define KERNEL_DELAY 0

class Job_Governor_Process;

class Process;

class Kernel {
	private:
		struct Process_Comparator {
    		bool operator()(const Process* a, const Process* b) const {
				if(a -> get_priority() == b -> get_priority()) {
					if(a -> get_runtime() == b -> get_runtime()) {
						return false;
					}
					else {
						return a -> get_runtime() + CPU_DEFAULT_TIMER_VALUE > b -> get_runtime();
					}
				}
        		return a -> get_priority() < b -> get_priority();
    		}
		};

		Real_Machine* real_machine;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> ready_queue;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> blocked_queue;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> ready_stopped_queue;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> blocked_stopped_queue;
		// std::vector<Process*> running;
		std::vector<Process*> all_processes;
		std::list<Resource*> resources;

	public:
		std::queue<Job_Governor_Process*> console_holder_q;

		bool line_consumed;

		Kernel(Real_Machine* real_machine);

		// for system resources
		void request_resource(Process* process, Resource_Type resource_type);

		// for dynamic resources
		void request_resource(Process* process, Resource* resource);

		Resource* get_resource(Process* process, Resource_Type resource_type);

		// returns the created resoursces ID
		uint32_t init_resource(Resource_Type resource_type, Process* owner);
		uint32_t init_resource(Resource_Type resource_type, Process* owner, std::string buffer);

		// used for system resources
		void release_resource(Resource_Type resource_type, std::string updated_buffer = "");
		void release_resource_id(uint32_t resc_id, std::string updated_buffer = "");

		// used for dynamic resources, like "from loader" or "from interrupt"
		void release_resource_for(uint32_t resc_id, uint32_t for_pid, std::string updated_buffer = "");

		// used for non dynamic resources that are meant for a specific process, like interrupt
		void release_resource_for(Resource_Type resource_type, uint32_t for_pid, std::string updated_buffer = "");

		void delete_resource(Process* process, Resource_Type resource_type);

		void return_resource_to_owner(Resource* resource);

		// void release_resource(Resource* resource);

		// used for system resources
		Resource* get_resource_by_type(Resource_Type resource_type);

		void run();

		void kill_processes_except(Process* process);

		void request_to_kill(uint32_t pid);

		void assign_vm(uint32_t vm_pid, Virtual_Machine* vm);

		void destroy_resources();

		Channel_Device* get_channel_device();
		Hard_Disk* get_hard_disk();
		CPU* get_cpu();
		Memory* get_memory();

		// returns the process id of the created process
		template<typename T>
		uint32_t create_process(Process* parent_process, std::vector<Process*> friend_processes, std::string username) {
			Process* process = new T(this, parent_process, friend_processes, username);
			process -> set_state(Process_State::READY);
			this -> ready_queue.push(process);
			this -> all_processes.push_back(process);
			return process -> get_unique_id();
		};

		void print_running_proc(Process* running_proc);

		// forces a ready_stopped process to run
		void unstop_ready(uint32_t pid);

		void lower_priority(uint32_t pid);

		Process* get_proc_by_id(uint32_t pid);

		uint32_t get_first_free_loader_p_resc();

		void delete_resource(Resource* resc);
};


#endif // KERNEL_H_INCLUDED
