#include "../include/printer_process.h"

// turns a regular process into a printer process
// kind of like poilymorphism
Process* init_printer_process(Process* process) {	
	if(!process) {
		return NULL;
	}

	process -> execute = &printer_process_execute;

	return process;
}

int8_t printer_process_execute(Process* process) {
	if(!printer) {
		return -1;
	}
	
	// switch the current step
	switch(printer -> process.current_step) {
		case PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY:
			break;
		case PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE:
			break;
		case PRINTER_PROCESS_EXECUTING_XCHG:
			break;	
		case PRINTER_PROCESS_FREE_CHANNEL_DEVICE:
			break;
		default:
			break;
	
	}

	return 0;
}
