#ifndef LOADER_PROCESS_H_INCLUDED
#define LOADER_PROCESS_H_INCLUDED

#include "process.h"

enum class Loader_Process_Steps{
    LOADER_PROCESS_BLOCKED_WAITING_FOR_LOADER_PACKAGE_RESOURCE,
    LOADER_PROCESS_BLOCKED_WAITING_FOR_CHANNEL_DEVICE_RESOURCE,
    LOADER_PROCESS_SET_CHANNEL_DEVICE_REGISTERS_AND_XCHG,
    LOADER_PROCESS_FREE_RESOURCE_CHANNEL_DEVICE,
    LOADER_PROCESS_FREE_RESOURCE_SUPERVISOR_MEMORY,
    LOADER_PROCESS_FREE_RESOURCE_FROM_LOADER_FOR_JOB_GOVERNER
};

class Loader_Process: public Process{
    private:
        Loader_Process_Steps step;
        uint32_t current_program_len;
        
    public:
        Loader_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Loader_Process();
        Process_State execute() override;
};

#endif // LOADER_PROCESS_H_INCLUDED