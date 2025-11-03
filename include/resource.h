#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <stdint.h>
#include "process.h"
#include "kernel.h"

#define RESOURCE_MEMORY_STRING_MAX_LENGTH 256

typedef struct Process_List Process_List;
typedef struct Resource_List Resource_List;
typedef struct Element_List Element_List;

static char message[RESOURCE_MEMORY_STRING_MAX_LENGTH];

typedef enum Resource_Type {
	RESOURCE_MOS_END,
	RESOURCE_SYSTEM_COMMAND,
	RESOURCE_HARD_DISK,
	RESOURCE_USER_MEMORY,
	RESOURCE_SUPERVISOR_MEMORY,
	RESOURCE_TASK_IN_SUPERVISOR,
	RESOURCE_STRING_IN_MEMORY,
	RESOURCE_LOADER_PACKAGE,
	RESOURCE_PIE_IN_THE_OVEN,
	RESOURCE_NON_EXISTANT,
	RESOURCE_CHANNEL_DEVICE,
	RESOURCE_USER_INPUT,
	RESOURCE_INTERRUPT,
	RESOURCE_FROM_INTERRUPT,
	RESOURCE_FROM_LOADER,
	RESOURCE_FROM_USER_INTERFACE
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


const char* get_string_in_memory();

void set_string_in_memory(const char* msg, uint16_t length);

int8_t check_resource_owned(Resource_List* resource_list, uint8_t resource_number);

#endif // RESOURCE_H_INCLUDED* resour
