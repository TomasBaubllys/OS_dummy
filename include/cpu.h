#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdint.h>
#include "util.h"
#include "channel_device.h"
#include "saved_registers.h"

#define CPU_DEFAULT_TIMER_VALUE 10
#define CPU_USER_MODE 0
#define CPU_SUPERVISOR_MODE 1

#define CPU_DEFAULT_PC_VALUE 0x0000

#define CPU_UNKNOWN_REGISTER 0xff

#define RA_CODE 0x7261
#define RB_CODE 0x7262
#define RC_CODE 0x7263

#ifdef __cplusplus
extern "C" {
#endif

typedef enum Cpu_Pi_Type {
	CPU_PI_NONE,
	CPU_PI_INVALID_ADDRESS,
	CPU_PI_INVALID_OPCODE,
	CPU_PI_INVALID_ASSIGNMENT,
	CPU_PI_OVERFLOW,
	CPU_PI_DIVISION_BY_ZERO
} Cpu_Pi_Type;

typedef enum Cpu_Si_Type {
	CPU_SI_NONE,
	CPU_SI_GEDA,
	CPU_SI_PUTA,
	CPU_SI_PSTR,
	CPU_SI_LW,
	CPU_SI_SW,
	CPU_SI_BP,
	CPU_SI_BG,
	CPU_SI_STOP
} Cpu_Si_Type;

#define CPU_MSG_INVALID_ADDRESS "Invalid address \n"
#define CPU_MSG_INVALID_OPCODE "Invalid opcode\n"
#define CPU_MSG_INVALID_ASSIGNMENT "Invalid assignment\n"
#define CPU_MSG_DIVISION_BY_ZERO "Division by zero \n"
#define CPU_MSG_OVERFLOW "Overflow \n"


#define INTERUPT_STOP -1
#define SEMAFOR_BUSY 1
#define SEMAFOR_FREE 0

typedef struct CPU {
	uint16_t pc;			// program counter
	uint16_t pi;			// program interrupt register
	uint16_t si;			// supervisor interrupt register
	uint16_t tr;			// page table register

	uint8_t ti;				// timer register
	uint8_t sf;				// flag register
	uint8_t mr;				// mode register
	uint8_t ss;				// semafor register

	uint32_t ra;			// general purpose register
	uint32_t rb;			// general purpose register
	uint32_t rc;			// general purpose register, also used for loops
	uint16_t ptr;

	Channel_Device* channel_device;
	Memory* memory;
} CPU;

// initializes cpu
int init_cpu(CPU* cpu, Memory* memory, Channel_Device* channel_device);

// checks interrupts (PI and SI)
int interrupt(CPU* cpu);

// checks timer (TI) 
uint8_t check(CPU* cpu);

// sets all registers to 0
int reset_cpu(CPU* cpu);

Saved_Registers cpu_save_regs(CPU* cpu);

void cpu_load_regs(CPU* cpu, Saved_Registers saved_regs);

#ifdef __cplusplus
}
#endif

#endif // CPU_H_INCLUDED
