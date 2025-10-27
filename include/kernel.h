#ifndef KERNEL_H_INCLUDED
#define KERNEL_H_INCLUDED

#include <stdint.h>
#include <real_machine.h>

// forward declaration
typedef struct Process_List;
typedef struct Resource_List;


typedef struct Kernel {
	Real_machine* real_machine;
	struct Process_List processes;
	struct Process_List running_processes;
	struct Process_List read_processes;
	struct Resource_List resources;
} Kernel;


#endif // KERNEL_H_INCLUDED
