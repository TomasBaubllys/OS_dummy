#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <stdint.h>
#include "real_machine.h"

// forward declaration
//typedef struct Process_List Process_List;
//typedef struct Resource_List Resource_List;

class Process;
class Resource;


struct Kernel {
	Real_machine* real_machine;
	std::vector<Process*> processes;
	std::vector<Process*> running_processes;
	std::vector<Process*> ready_processes;
	std::vector<Resource*> resources;

	std::string string_in_memory;

	void request_resource(Process* process, Resource_Type resource_t);
} Kernel;


#endif // KERNEL_H_INCLUDED
