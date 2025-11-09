#ifndef MAIN_PROCESS_PROCESS_H_DEFINED
#define MAIN_PROCESS_PROCESS_H_DEFINED

#include "process.h"

typedef enum Main_Process_Process_Steps{
    MAIN_PROCESS_PROCESS_BLOCKED_WAITING_FOR_SYSTEM_COMMAND,
    MAIN_PROCESS_PROCESS_CHECK_IF_PIE_IN_THE_OVEN_FREE,
    MAIN_PROCESS_PROCESS_CHECK_IF_ITS_SHUT_DOWN,
    MAIN_PROCESS_PROCESS_CREAhE_RESOURCE_MOS_END,
    MAIN_PROCESS_PROCESS_CHECK_IF_ITS_KILL,
    MAIN_PROCESS_PROCESS_REMOVE_PROCESS_JOB_GOVERNOR_1,
    MAIN_PROCESS_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_NONEXISTING_SYSTEM_COMMAND,
    MAIN_PROCESS_PROCESS_CHECK_RUNTIME_0,
    MAIN_PROCESS_PROCESS_CREATE_PROCESS_JOB_OVERNOR_WITH_PIE_IN_THE_OVEN_RESOURCE,
    MAIN_PROCESS_PROCESS_REMOVE_PROCESS_JOB_GOVERNER_2

};

class Main_Process_Process: public Process{
    private:
        Main_Process_Process_Steps steps;
    
    public:
        Main_Process_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Main_Process_Process();
        virtual int8_t execute() override;
};


#endif // MAIN_PROCESS_PROCESS_H_DEFINED