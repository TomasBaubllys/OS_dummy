#include "../../include/processes/printer_process.h"
#include "../include/resource.h"

Printer_Process::Printer_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) :
	Process(kernel, parent_process, friend_processes, username, Process_Priorities::PRINTER_PRIORITY)
{	

}

Printer_Process::~Printer_Process() {

}

Process_State Printer_Process::execute() {
	switch (this -> step){
		case Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY_RESOURCE:
			if(this -> owns_resource(Resource_Type::STRING_IN_MEMORY)) {
				this -> step = Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE;
				return Process_State::READY;
			}

			return Process_State::BLOCKED;
		case Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE:
			if(this -> owns_resource(Resource_Type::CHANNEL_DEVICE)) {
				this -> step = Printer_Process_Steps::PRINTER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG;
				return Process_State::READY;
			}

			return Process_State::BLOCKED;
		case Printer_Process_Steps::PRINTER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG:
			Channel_Device* ch_dev = this -> kernel -> get_channel_device();
			ch_dev -> st = MSG_IN_MEMORY;
			ch_dev -> dt = IO_STREAM;
			ch_dev -> sa = (uint32_t)(this -> kernel -> string_in_memory.c_str());
			ch_dev -> cb = this -> kernel -> string_in_memory.size();
			ch_dev -> of = 0;  

			xchg(ch_dev);
			this -> step = Printer_Process_Steps::PRINTER_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE; 
			return Process_State::READY;
		case Printer_Process_Steps::PRINTER_PROCESS_FREE_CHANNEL_DEVICE_RESOURCE:
			this -> kernel -> release_resource(Resource_Type::CHANNEL_DEVICE);	

			this -> step = Printer_Process_Steps::PRINTER_PROCESS_BLOCKED_WAITING_FOR_STRING_IN_MEMORY_RESOURCE;
			return Process_State::READY;
		default:
			return Process_State::BLOCKED_STOPPED;
	}

	return Process_State::BLOCKED_STOPPED;
}
