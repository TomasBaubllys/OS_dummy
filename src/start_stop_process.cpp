#include "../include/start_stop_process.h"

Start_Stop_Process::Start_Stop_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(saved_registers, unique_id, kernel, cpu, parent_process, friend_processes, username)
{

}

Start_Stop_Process::~Start_Stop_Process() {

}

int8_t Start_Stop_Process::execute() {
    switch (this -> current_step)
    {
        case Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_RESOURCES: {
            
            break;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_PERMANENT_RESOURCES: {

            break;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_BLOCKED_WAITING_FOR_MOS_END : {

            break;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_KILL_SYSTEM_PROCESSES : {

            break;
        }
        case Start_Stop_Process_Steps::START_STOP_PROCESS_KILL_SYSTEM_RESOURCES : {

            break;
        }
    
        default: {
            break;
        }
    }
}