#include "../include/printer_process.h"

int8_t init_printer_process() {

	return 0;
}

int8_t execute(Printer_Process* printer) {
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
