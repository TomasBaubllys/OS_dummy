#include "../include/printer_process.h"
#include "../include/resource.h"

Printer_Process::Printer_Process(Saved_Registers saved_registers, uint32_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) :
	Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username)
{	

}

Printer_Process::~Printer_Process() {

}

int8_t Printer_Process::execute() {
	switch (this -> step){
		case Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY_RESOURCE:
			if(this -> owns_resource(Resource_Type::RESOURCE_STRING_IN_MEMORY)) {
				this -> step = Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE;
			}

			return Process_State::BLOCKED;
		case Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE:
			if(this -> owns_resource(Resource_Type::RESOURCE_CHANNEL_DEVICE)) {
				this -> step = Printer_Process_Steps::PRINTER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG;
			}

			return Process_State::BLOCKED;
		case Printer_Process_Steps::PRINTER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG:
			Channel_device* ch_dev = this -> cpu -> channel_device;
			ch_dev -> st = MSG_IN_MEMORY;
			ch_dev -> dt = IO_STREAM;
			ch_dev -> sa = (uint32_t)(this -> kernel -> string_in_memory.c_str());
			ch_dev -> cb = this -> kernel -> string_in_memory.size();
			ch_dev -> of = 0;  

			xchg(ch_dev);
			this -> step = Printer_Process_Steps::PRINTER_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE; 
			return Process_State::READY;
		case Printer_Process_Steps::PRINTER_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE:
			/**
			 * 
			 * NOT IMPLEMENTED YET
			 * 
			 */
			this -> step = Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY_RESOURCE;
			break;
		default:
			return -1;
	}

	return 0;
}
