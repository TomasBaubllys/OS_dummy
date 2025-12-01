#include "../../include/processes/loader_process.h"
#include <string>
#include <sstream>

Loader_Process::Loader_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::LOADER_PRIORITY){

}

Loader_Process::~Loader_Process(){

}

Process_State Loader_Process::execute(){
    switch (this -> step){
        case Loader_Process_Steps::LOADER_PROCESS_BLOCKED_WAITING_FOR_LOADER_PACKAGE_RESOURCE: {
            if(this -> owns_resource(Resource_Type::LOADER_PACKAGE)) {
                Resource* resc = this -> get_owned_resource(Resource_Type::LOADER_PACKAGE);
                std::string buffer = resc -> get_buffer();
                
                std::stringstream ss(buffer);
                // program len is always the size of supervisor
                ss >> this -> u_id_buffer >> this -> current_program_len >> this -> saved_registers.ptr;

                this -> step = Loader_Process_Steps::LOADER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::LOADER_PACKAGE);
            return Process_State::BLOCKED;
        }
        case Loader_Process_Steps::LOADER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE:
            if(this -> owns_resource(Resource_Type::CHANNEL_DEVICE)) {
                this -> step = Loader_Process_Steps::LOADER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::CHANNEL_DEVICE);
            return Process_State::BLOCKED;
        case Loader_Process_Steps::LOADER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG:
            Channel_Device* ch_dev = this -> kernel -> get_channel_device();
            CPU* cpu = this -> kernel -> get_cpu();
            cpu -> ptr = this -> saved_registers.ptr;
            Memory* mem = this -> kernel -> get_memory();
            
            for(uint32_t i = 0; i < MEM_SUPERVISOR_PAGE_COUNT; ++i) {
                uint16_t r_page = translate_to_real_address(mem, i * MEM_PAGE_BYTE_COUNT) / (MEM_PAGE_BYTE_COUNT);
                ch_dev -> dt = USER_MEM;
                ch_dev -> db = r_page;
                ch_dev -> cb = this -> current_program_len > MEM_PAGE_BYTE_COUNT? MEM_PAGE_BYTE_COUNT : this -> current_program_len;
                ch_dev -> st = SUPER_MEM;
                ch_dev -> sb = MEM_SUPERVISOR_PAGE_BEGIN + i;
                ch_dev -> of = 0;
                ch_dev -> sa = PROGRAM_MARKER_SIZE;
                xchg(ch_dev);

                this -> current_program_len -=  ch_dev -> cb;		

                if(this -> current_program_len == 0) {
                    break;
                }
            }

            this -> step = Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_CHANNEL_DEVICE;
            return Process_State::READY;
        case Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_CHANNEL_DEVICE:
            this -> kernel -> release_resource(Resource_Type::CHANNEL_DEVICE);
            this -> step = Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_SUPERVISOR_MEMORY;
            return Process_State::READY;

        case Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_SUPERVISOR_MEMORY:
            this -> kernel -> release_resource(Resource_Type::SUPERVISOR_MEMORY);
            this -> step = Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_FROM_LOADER_FOR_JOB_GOVERNER;
            return Process_State::READY;

        case Loader_Process_Steps::LOADER_PROCESS_FREE_RESOURCE_FROM_LOADER_FOR_JOB_GOVERNER: {
            this -> kernel -> release_resource_for(Resource_Type::FROM_LOADER, this -> u_id_buffer);
            this -> step = Loader_Process_Steps::LOADER_PROCESS_BLOCKED_WAITING_FOR_LOADER_PACKAGE_RESOURCE;
            return Process_State::READY;
        }
        default:
            break;
    }

    return Process_State::BLOCKED_STOPPED;
}