#ifndef INTERRUPT_RPOCESS_H_INCLUD
#define INTERRUPT_RPOCESS_H_INCLUDED

#include "process.h"

enum class Interrupt_Process_Steps{
    INTERRUPT_RPOCESS_BLOCKED_WAITING_FOR_INTERRUPT_RESOURCE,
    INTERRUPT_RPOCESS_IDENTIFY_INTERRUPT,
    INTERRUPT_RPOCESS_RECOGNIZE_JOB_GOVERNOR_RESPONSIBLE_FOR_INTERRUPT,
    INTERRUPT_RPOCESS_FREE_FROM_INTERRUPT_RESOURCE
};

class Interrupt_Process: public Process{
    private:
        Interrupt_Process_Steps current_step;
    public:
        Interrupt_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Interrupt_Process();
        virtual int8_t execute() override;
};


#endif // INTERRUPT_RPOCESS_H_INCLUDED