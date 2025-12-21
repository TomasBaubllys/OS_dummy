#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <stdint.h>
// #include "kernel.h"
#include <queue>
#include <string>

class Kernel;
class Process;

#define RESOURCE_MEMORY_STRING_MAX_LENGTH 256
#define NOT_DEDICATED_VAL 0

static uint32_t resource_id_pool = 0;

// System resources:
// these resources are "singletons" and can only be accessed one at a time
/*
	MOS_END,
	SYSTEM_COMMAND,
	HARD_DISK,
	USER_MEMORY,
	SUPERVISOR_MEMORY,
	TASK_IN_SUPERVISOR,
	STRING_IN_MEMORY,
	CONSOLE,
	PIE_IN_THE_OVEN,
	NON_EXISTANT,
	CHANNEL_DEVICE,
	INTERRUPT,
	FROM_USER_INTERFACE,
*/

// Dynamic resources:
// these resources can be "created by a process"
/*
	LOADER_PACKAGE,
	USER_INPUT,
	FROM_LOADER,
	FROM_INTERRUPT,
*/

enum class Resource_Type : uint16_t {
	MOS_END = 				0x0000,
	SYSTEM_COMMAND = 		0x0001,
	HARD_DISK = 			0x0002,
	USER_MEMORY = 			0x0003,
	SUPERVISOR_MEMORY =		0x0004 ,
	TASK_IN_SUPERVISOR = 	0x0005,
	STRING_IN_MEMORY = 		0x0006,
	LOADER_PACKAGE = 		0x0007,
	PIE_IN_THE_OVEN = 		0x0008,
	CONSOLE = 				0x0009,
	NON_EXISTANT = 			0x000A,
	CHANNEL_DEVICE = 		0x000B,
	USER_INPUT = 			0x000C,
	INTERRUPT = 			0x000D,
	FROM_INTERRUPT = 		0x000E,
	FROM_LOADER = 			0x000F,
	FROM_USER_INTERFACE = 	0x0010,
	DYNAMIC = 				0x0011,
	NONE = 					0x0012
};

class Resource {
	private:
		uint32_t unique_id;

		std::string buffer;

		Process* owner;
		Process* user;
		Resource_Type resource_type;

		// process id to which is dedicated.... (if empty, it means its free for grabs)
		uint32_t dedicated_to;

	public:
		Resource(uint32_t unique_id, Resource_Type type, Process* owner = nullptr);

		Resource_Type get_resource_type() const;

		void enqueue(Process* process);

		bool is_free();

		void free_resource();

		void assign(Process* process);

		std::string get_buffer();

		size_t get_buffer_size();

		void set_buffer(std::string buffer);

		bool is_dedicated();

		uint32_t get_dedicated();

		void set_dedicated(uint32_t pid);

		uint32_t get_owner_id();

		uint32_t get_uid();

		void return_to_owner();

		Process* get_owner();

		Process* get_user();
};

#endif // RESOURCE_H_INCLUDED
