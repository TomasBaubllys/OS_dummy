#ifndef VIRTUAL_MACHINE_H_INCLUDED
#define VIRTUAL_MACHINE_H_INCLUDED

#include "real_machine.h"

#define VM_DEFAULT_PC_VAL 0
#define VM_VIRTUAL_MACHINE_BLOCK_COUNT 16
#define VM_MAX_VIRTUAL_ADDRESS 0x400
#define VM_MAX_VIRTUAL_ADDDRESS_EXCEEDED 0xffff
#define VM_REAL_MACHINE_NULL 0xfffe

#define VM_STEPPING_MODE_NEXT_COM "NEXT COMMAND: "
#define VM_STEPPING_PRESS_KEY "Press ENTER to continue...\n"

#define VM_EXEC_FAILED_NULL_ERR "Virtual machine is null execution cancelled\n"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Virtual_Machine {
	CPU* cpu;
	Memory* memory;
} Virtual_Machine;

// initializes virtual machine
int init_virtual_machine(Virtual_Machine* virtual_machine, CPU* cpu, Memory* memory);

// destroys virtual machine
int destroy_virtual_machine(Virtual_Machine* virtual_machine);

// executes a command at virtual pc
void virtual_machine_execute(Virtual_Machine* virtual_machine);

#ifdef __cplusplus
}
#endif

#endif // VIRTUAL_MACHINE_H_INCLUDED
