#ifndef INTERRUPT_RPOCESS_H_INCLUD
#define INTERRUPT_RPOCESS_H_INCLUDED

#include "process.h"

enum class Interrupt_Process_Steps{
    INTERRUPT_PROCESS_BLOCKED_WAITING_FOR_INTERRUPT_RESOURCE,
    INTERRUPT_PROCESS_IDENTIFY_INTERRUPT,
    INTERRUPT_PROCESS_RECOGNIZE_JOB_GOVERNOR_RESPONSIBLE_FOR_INTERRUPT,
    INTERRUPT_PROCESS_FREE_FROM_INTERRUPT_RESOURCE
};

class Interrupt_Process: public Process{
    private:
        Interrupt_Process_Steps step;
        
    public:
        Interrupt_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Interrupt_Process();
        Process_State execute() override;
};


#endif // INTERRUPT_RPOCESS_H_INCLUDED