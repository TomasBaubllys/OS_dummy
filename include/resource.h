#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <stdint.h>
#include "kernel.h"
#include <vector>
#include "resource_element.h"

#define RESOURCE_MEMORY_STRING_MAX_LENGTH 256

typedef struct Process_List Process_List;
typedef struct Resource_List Resource_List;
typedef struct Element_List Element_List;

static char message[RESOURCE_MEMORY_STRING_MAX_LENGTH];

enum class Resource_Type : uint16_t {
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
};

class Resource {
	private:
		uint32_t unique_id;

		Process* creator;

		// pair of pointer to all waiting processes and vector of uint32_t of how many of the resourse they need
		std::pair<std::vector<Process*>, std::vector<uint32_t>> waiting_list_and_count;
		std::vector<Process*> friend_list;
			//Process_List* waiting_list;
			//Process_List* friend_list;
			//uint32_t* waiting_count;
		Kernel* kernel;

		// pointer to vector of all resources
		std::vector<Resource*> all_resources;
			//Resource_List* all_resources;
		Resource_Type resource_type;

		// pointer to the vector of this resource elements
		std::vector<Resource_Element>* elements; 
			//Element_List* elements;

		// pointer to the vector of resource elements that are currently being waited on
		std::vector<Resource_Element>* currently_waiting_elements;
			//Element_List* waiting_process_pointers;

	public:
		Resource(uint32_t unique_id, Resource_Type type, Process* creator, Kernel* kernel, std::vector<Resource*> all_resources);

		Resource_Type get_resource_type();
};

/*
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
*/

#endif // RESOURCE_H_INCLUDED
