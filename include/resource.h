#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <stdint.h>
#include "process.h"
#include "kernel.h"

typedef struct Process_List;
typedef struct Resource_List;
typedef struct Element_List;

typedef enum Resource_Type {
	MOS_END,
	SYSTEM_COMMAND,
	HARD_DISK,
	USER_MEMORY,
	SUPERVISOR_MEMORY,
	TASK_IN_SUPERVISOR,
	STRING_IN_MEMORY,
	LOADER_PACKAGE,
	PIE_IN_THE_OVEN,
	NON_EXISTANT,
	CHANNEL_DEVICE,
	USER_INPUT,
	INTERRUPT,
	FROM_INTERRUPT,
	FROM_LOADER,
	FROM_USER_INTERFACE
} Resource_Type;

typedef struct Resource {
	uint32_t unique_id;
	struct Process* creator;
	struct Process_List* waiting_list;
	struct Process_List* friend_list;
	uint32_t* waiting_count;
	struct Kernel* kernel;
	struct Resource_List* all_resources;
	Resource_Type resource_type;
	struct Element_List* elements;
	struct Element_List* waiting_process_pointers;
} Resource;

#endif // RESOURCE_H_INCLUDED
