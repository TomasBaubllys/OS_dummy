#ifndef CHANNEL_DEVICE_H_INCLUDED
#define CHANNEL_DEVICE_H_INCLUDED

#include <stdint.h>
#include "hard_disk.h"
#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Channel_Device {
	uint16_t sb;			// number of the block to copy from
	uint16_t db;			// number of the block to copy to
	uint8_t st;				// number of the object which we are going to copy from
	uint32_t cb;			// number of bytes to copy (one byte is not used)
	uint16_t of;			// stores the offset value
	uint8_t dt;				// number of the object to copy to
	uint32_t sa;			// symbol register
	char* _sa_ptr;

	char* _file_name;

	Memory* memory;			// bruh
	Hard_Disk* hard_disk;	// bruh
} Channel_Device;

enum Object_numbers {
	USER_MEM = 1,
	IO_STREAM,
	SHARED_MEM,
	RA_REG,
	SUPER_MEM,
	HD_DISK,
	MSG_IN_MEMORY,
	FILE_CHECK
};

// initializes channel device
int init_channel_device(Channel_Device* channel_dev, Memory* memory, Hard_Disk* Hard_Disk);

// sets all registers to 0
void reset_channel_device(Channel_Device* channel_device);

// calls channel device
int xchg(Channel_Device* channel_device);

const char* get_string_in_memory();

void set_string_in_memory(const char* msg, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif // CHANNEL_DEVICE_H_INCLUDED
