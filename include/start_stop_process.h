#ifndef START_STOP_PROCESS_H_INCLUDED
#define START_STOP_PROCESS_H_INCLUDED

#include "process.h"

typedef enum Start_Stop_Process_Steps{
    START_STOP_PROCESS_INITIALIZE_RESOURCES,
    START_STOP_PROCESS_INITIALIZE_PERMANENT_RESOURCES,
    START_STOP_PROCESS_BLOCKED_WAITING_FOR_MOS_END,
    START_STOP_PROCESS_KILL_SYSTEM_PROCESSES,
    START_STOP_PROCESS_KILL_SYSTEM_RESOURCES
} Start_Stop_Process_Steps;

class Start_Stop_Process: public Process {
    private:
        Start_Stop_Process_Steps steps;

    public:
        Start_Stop_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Start_Stop_Process();

        int8_t execute() override;
};



#endif //START_STOP_PROCESS_H_INCLUDED