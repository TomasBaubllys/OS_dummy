#include "../include/printer_process.h"
#include "../include/resource.h"

Printer_Process::Printer_Process(Saved_Registers saved_registers, uint32_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) :
	saved_registers(saved_registers),
	unique_id(unique_id),
{	

}

Printer_Process::~Printer_Process() {

}

int8_t Printer_Process::execute() {

}


/*
//8 turns a regular process into a printer process
// kind of like poilymorphism
Process* init_printer_process(Process* process) {	
	if(!process) {
		return NULL;
	}

	process -> current_step = 0;

	process -> execute = &printer_process_execute;

	return process;
}

int8_t printer_process_execute(Process* printer) {
	if(!printer) {
		return -1;
	}
	
	// switch the current step
	switch(printer -> current_step) {
		case PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY:
			// tikrinti ar gautas resursas
			// jei taip --> ++current_step;
			if(printer -> owned_resources){
				if(check_resource_owned(printer -> owned_resources, RESOURCE_STRING_IN_MEMORY)){
					++(printer -> current_step);
				}
			}

			break;
		case PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE:
			// tikrinti ar gautas resursas
			// jei taip --> ++current_step
			if(printer -> owned_resources){
				if(check_resource_owned(printer -> owned_resources, RESOURCE_CHANNEL_DEVICE)){
					++(printer -> current_step);
				}
			}
			break;
		case PRINTER_PROCESS_EXECUTING_XCHG:
			printer -> cpu -> channel_device -> st = MSG_IN_MEMORY;
			printer -> cpu -> channel_device -> dt = IO_STREAM;
			xchg(printer -> cpu -> channel_device);

			++(printer -> current_step);
			break;	
		case PRINTER_PROCESS_FREE_CHANNEL_DEVICE:
			//huhuheuesfddskdslkfljasjkdf

			break;
		default:
			break;
	
	}

	return 0;
}
/*