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

		void add_process(Process* process);

		void run();
};


#endif // KERNEL_H_INCLUDED
