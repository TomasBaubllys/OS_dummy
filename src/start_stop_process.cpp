#include "../include/start_stop_process.h"

Start_Stop_Process::Start_Stop_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::START_STOP_PRIORITY), step(Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_RESOURCES)
{

}

Start_Stop_Process::~Start_Stop_Process() {

}

Process_State Start_Stop_Process::execute() {
    switch (this -> step)
    {
        case Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_RESOURCES: {
            this -> kernel -> init_resource(Resource_Type::SYSTEM_COMMAND);
            this -> kernel -> init_resource(Resource_Type::HARD_DISK);
            this -> kernel -> init_resource(Resource_Type::USER_MEMORY);
            this -> kernel -> init_resource(Resource_Type::SUPERVISOR_MEMORY);
            this -> kernel -> init_resource(Resource_Type::STRING_IN_MEMORY);
            this -> kernel -> init_resource(Resource_Type::PIE_IN_THE_OVEN);
            this -> kernel -> init_resource(Resource_Type::NON_EXISTANT);
            this -> kernel -> init_resource(Resource_Type::CHANNEL_DEVICE);
            this -> kernel -> init_resource(Resource_Type::USER_INPUT);
            this -> kernel -> init_resource(Resource_Type::INTERRUPT);
            this -> kernel -> init_resource(Resource_Type::FROM_USER_INTERFACE);
            this -> step = Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_PERMANENT_RESOURCES;

            return Process_State::READY;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_INITIALIZE_PERMANENT_RESOURCES: {

            return Process_State::READY;
        }

        case Start_Stop_Process_Steps::START_STOP_PROCESS_BLOCKED_WAITING_FOR_MOS_END : {
            if(this -> owns_resource(Resource_Type::MOS_END)) {
                this -> step = Start_Stop_Process_Steps::START_STOP_PROCESS_KILL_SYSTEM_PROCESSES;
                return Process_State::READY;
            }

            return Process_State::BLOCKED;
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