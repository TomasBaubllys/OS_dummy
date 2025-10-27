#ifndef SAVED_REGISTERS_H_INCLUDED
#define SAVED_REGISTERS_H_INCLUDED

#include <stdint.h>

typedef struct Saved_Registers {
	uint16_t pc;
	uint16_t pi;
	uint16_t si;
	uint16_t tr;

	uint8_t ti;
	uint8_t sf;
	uint8_t mr;
	uint8_t ss;

	uint32_t ra;
	uint32_t rb;
	uint32_t rc;
	uint32_t ptr;
} Saved_Registers;

#endif // SAVED_REGISTERS_H_INCLUDED
