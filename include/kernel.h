#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <stdint.h>
#include "real_machine.h"
#include <unordered_map>
#include <string>
#include "../include/resource.h"

#define SYSTEM_USERNAME "system"

class Process;

class Kernel {
	private:
		struct Process_Comparator;

		Real_Machine* real_machine;
		std::priority_queue<Process*, std::vector<Process*>, Process_Comparator> ready_queue;
		std::vector<Process*> running;
		std::vector<Process*> all_processes;
		std::unordered_map<Resource_Type, Resource*> resources;

	public:
		std::string string_in_memory;
		
		Kernel(Real_Machine* real_machine);
		
		void request_resource(Process* process, Resource_Type resource_type);
		Resource* get_resource(Resource_Type resource_type);
		void init_resource(Resource_Type resource_type);
		void release_resource(Process* process, Resource_Type resource_type);

		void run();

		void kill_processes_except(Process* process);

		void destroy_resources();

		Channel_Device* get_channel_device();
		
		template<typename T>
		void create_process(Process* parent_process, std::vector<Process*> friend_processes, std::string username) {
			Process* process = new T(this, parent_process, friend_processes, username);
			process -> set_state(Process_State::READY);
			this -> ready_queue.push(process);
			this -> all_processes.push_back(process);
		};
};


#endif // KERNEL_H_INCLUDED
