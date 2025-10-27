#ifndef PRINTER_PROCESS_H_INCLUDED
#define PRINTER_PROCESS_H_INCLUDED

#include "process.h"

typedef enum Printer_Process_Steps {
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY,
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE,
	PRINTER_PROCESS_EXECUTING_XCHG,
	PRINTER_PROCESS_FREE_CHANNEL_DEVICE

} Printer_Process_Steps;

typedef struct Printer_Process{
    Process process;
    

} Printer_Process;

int8_t init_printer_process();

int8_t execute(Printer_Process* printer);

#endif // PROCESS_PRINTER_H_INCLUDED
