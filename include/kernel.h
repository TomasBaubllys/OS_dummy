#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <stdint.h>
#include "real_machine.h"
#include <unordered_map>
#include <string>
#include "../include/resource.h"
#include <list>

#define SYSTEM_USERNAME "system"
#define RMI_SHUTDOWN_COMMAND "$SHUTDOWN"
#define RMI_FILE_INPUT "F$" 
#define RMI_SYS_COMMAND "$"
#define RMI_KILL_COMMAND "$KILL"
#define STR_MEM_UNKNOWN_SYS_COM_ERR_MSG "Unknown system command!\n"


class Job_Governor_Process;

class Process;

class Kernel {
	private:
		struct Process_Comparator;

		Real_Machine* real_machine;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> ready_queue;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> blocked_queue;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> ready_stopped_queue;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> blocked_stopped_queue;
		// std::vector<Process*> running;
		std::vector<Process*> all_processes;
		std::list<Resource*> resources; 

	public:
		Job_Governor_Process* current_console_holder;

		Kernel(Real_Machine* real_machine);
		
		// for system resources
		void request_resource(Process* process, Resource_Type resource_type);

		// for dynamic resources
		void request_resource(Process* process, Resource* resource);

		Resource* get_resource(Process* process, Resource_Type resource_type);

		void init_resource(Resource_Type resource_type, Process* owner);
		void init_resource(Resource_Type resource_type, Process* owner, std::string buffer);

		// used for system resources
		void release_resource(Resource_Type resource_type, std::string updated_buffer = "");
		
		// used for dynamic resources, like "from loader" or "from interrupt"
		void release_resource_for(Resource_Type resource_type, uint32_t for_pid, std::string updated_buffer = "");

		// used for dynamic resources
		// void release_resource(Resource* resource);

		// used for system resources
		Resource* get_resource_by_type(Resource_Type resource_type);

		void run();

		void kill_processes_except(Process* process);

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
};


#endif // KERNEL_H_INCLUDED
