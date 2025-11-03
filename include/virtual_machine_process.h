#ifndef VIRTUAL_MACHINE_PROCESS_H_INCLUDED
#define VIRTUAL_MACHINE_PROCESS_H_INCLUDED

#include "process.h"

typedef enum Virtual_Machine_Process_Steps {
	VIRTUAL_MACHINE_PROCESS_TO_USER_MODE,
	VIRTUAL_MACHINE_PROCESS_EXEC_USER_PROGRAM,
	VIRTUAL_MACHINE_PROCESS_FREE_INTERRUPT

} Virtual_Machine_Process_Steps;

Process* init_virtual_machine_process(Process* process);

int8_t virtual_machine_process_execute(Process* virtual_machine);

#endif // VIRTUAL_MACHINE_PROCESS_H_INCLUDED
