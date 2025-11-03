#include "../include/virtual_machine_process.h"

Process* init_virtual_machine_process(Process* process) {
	if(!process) {
		return NULL;
	}

	process -> execute = &virtual_machine_process_execute;

	return process;
}

int8_t virtual_machine_process_execute(Process* virtual_machine) {
	if(!virtual_machine) {
		return -1;
	}

	switch(virtual_machine -> process.current_step) {
		case VIRTUAL_MACHINE_PROCESS_TO_USER_MODE: 
			break;
		case VIRTUAL_MACHINE_PROCESS_EXEC_USER_PROGRAM:
			break;
		case VIRTUAL_MACHINE_PROCESS_FREE_INTERRUPT:
			break;
		default: 
			break;
	}
}
