#ifndef PRINTER_PROCESS_H_INCLUDED
#define PRINTER_PROCESS_H_INCLUDED

#include "process.h"

typedef enum Printer_Process_Steps {
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY,
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE,
	PRINTER_PROCESS_EXECUTING_XCHG,
	PRINTER_PROCESS_FREE_CHANNEL_DEVICE

} Printer_Process_Steps;

Process* init_printer_process(Process* process);

int8_t printer_process_execute(Process* printer);

#endif // PROCESS_PRINTER_H_INCLUDED
