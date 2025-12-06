#ifndef START_STOP_PROCESS_H_INCLUDED
#define START_STOP_PROCESS_H_INCLUDED

#include "process.h"

#define SSP_SHUTDOWN_MSG "Bye bye..." 

#define START_STOP_NAME "Start_Stop_Process"

enum class Start_Stop_Process_Steps{
    START_STOP_PROCESS_INITIALIZE_RESOURCES,
    START_STOP_PROCESS_INITIALIZE_SYSTEM_PROCESSES,
    START_STOP_PROCESS_BLOCKED_WAITING_FOR_MOS_END,
    START_STOP_PROCESS_KILL_SYSTEM_PROCESSES,
    START_STOP_PROCESS_KILL_SYSTEM_RESOURCES
};

class Start_Stop_Process: public Process {
    private:
        Start_Stop_Process_Steps step;

    public:
        Start_Stop_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Start_Stop_Process();

        Process_State execute() override;
};



#endif //START_STOP_PROCESS_H_INCLUDED