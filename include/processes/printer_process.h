#ifndef PRINTER_PROCESS_H_INCLUDED
#define PRINTER_PROCESS_H_INCLUDED

#include "process.h"

#define PRINTER_NAME "Printer_Process"

enum class Printer_Process_Steps : uint16_t {
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY_RESOURCE,
	PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE,
	PRINTER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG,
	PRINTER_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE
};

class Printer_Process: public Process{
	private:
		Printer_Process_Steps step;

	public:
		Printer_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
		~Printer_Process();

		Process_State execute() override;
};


/*Process* init_printer_process(Process* process);

int8_t printer_process_execute(Process* printer);*/

#endif // PROCESS_PRINTER_H_INCLUDED
