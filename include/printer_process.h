#ifndef PRINTER_PROCESS_H_INCLUDED
#define PRINTER_PROCESS_H_INCLUDED

#include "process.h"

typedef enum Printer_Process_Steps {
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY_RESORUCE,
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE,
	PRINTER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG,
	PRINTER_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE
} Printer_Process_Steps;

class Printer_Process: public Process{
	private:
		Printer_Process_Steps steps;

	public:
		Printer_Process(Saved_Registers saved_registers, uint32_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
		~Printer_Process();

		virtual int8_t execute() override;
};


/*Process* init_printer_process(Process* process);

int8_t printer_process_execute(Process* printer);*/

#endif // PROCESS_PRINTER_H_INCLUDED
