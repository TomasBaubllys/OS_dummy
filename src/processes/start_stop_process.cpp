#include "../../include/processes/start_stop_process.h"
#include "../../include/processes/idle_process.h"
#include "../../include/processes/interrupt_process.h"
#include "../../include/processes/main_process_process.h"
#include "../../include/processes/read_from_interface_process.h"
#include "../../include/processes/printer_process.h"
#include "../../include/kernel.h"
#include <iostream>

Start_Stop_Process::Start_Stop_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::START_STOP_PRIORITY), step(Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_RESOURCES)
{
    this -> saved_registers = {};
    this -> name = START_STOP_NAME;
}

Start_Stop_Process::~Start_Stop_Process() {

}

Process_State Start_Stop_Process::execute() {
    switch (this -> step)
    {
        case Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_RESOURCES: {
            // release half if these resources by default....
            this -> kernel -> init_resource(Resource_Type::SYSTEM_COMMAND, this);

            this -> kernel -> init_resource(Resource_Type::HARD_DISK, this);
            this -> kernel -> release_resource(Resource_Type::HARD_DISK);

            this -> kernel -> init_resource(Resource_Type::USER_MEMORY, this);
            this -> kernel -> release_resource(Resource_Type::USER_MEMORY);

            this -> kernel -> init_resource(Resource_Type::SUPERVISOR_MEMORY, this);
            this -> kernel -> release_resource(Resource_Type::SUPERVISOR_MEMORY);

            this -> kernel -> init_resource(Resource_Type::STRING_IN_MEMORY, this);

            this -> kernel -> init_resource(Resource_Type::CONSOLE, this);
            this -> kernel -> release_resource(Resource_Type::CONSOLE);

            this -> kernel -> init_resource(Resource_Type::PIE_IN_THE_OVEN, this);
            this -> kernel -> init_resource(Resource_Type::NON_EXISTANT, this);
            
            this -> kernel -> init_resource(Resource_Type::CHANNEL_DEVICE, this);
            this -> kernel -> release_resource(Resource_Type::CHANNEL_DEVICE);

            this -> kernel -> init_resource(Resource_Type::USER_INPUT, this);
            this -> kernel -> init_resource(Resource_Type::INTERRUPT, this);
            this -> kernel -> init_resource(Resource_Type::FROM_USER_INTERFACE, this);
            this -> step = Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_SYSTEM_PROCESSES;

            return Process_State::READY;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_SYSTEM_PROCESSES: {
            this -> kernel -> create_process<Idle_Process>(this, {}, SYSTEM_USERNAME);
            this -> kernel -> create_process<Interrupt_Process>(this, {}, SYSTEM_USERNAME);
            this -> kernel -> create_process<Main_Process_Process>(this, {}, SYSTEM_USERNAME);
            this -> kernel -> create_process<Read_From_Interface_Process>(this, {}, SYSTEM_USERNAME);
            this -> kernel -> create_process<Printer_Process>(this, {}, SYSTEM_USERNAME);

            this -> step = Start_Stop_Process_Steps::START_STOP_PROCESS_BLOCKED_WAITING_FOR_MOS_END;
            return Process_State::READY;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_BLOCKED_WAITING_FOR_MOS_END : {
            if(this -> owns_resource(Resource_Type::MOS_END)) {
                std::cout << SSP_SHUTDOWN_MSG << std::endl;
                this -> step = Start_Stop_Process_Steps::START_STOP_PROCESS_KILL_SYSTEM_PROCESSES;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::MOS_END);
            return Process_State::BLOCKED;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_KILL_SYSTEM_PROCESSES : {
            this -> kernel -> kill_processes_except(this);
            this -> step = Start_Stop_Process_Steps::START_STOP_PROCESS_KILL_SYSTEM_RESOURCES;
            return Process_State::READY;
        }
        case Start_Stop_Process_Steps::START_STOP_PROCESS_KILL_SYSTEM_RESOURCES : {
            this -> kernel -> destroy_resources();
            return Process_State::READY_STOPPED;
        }
    
        default: {
            break;
        }
    }

    return Process_State::BLOCKED_STOPPED;
}