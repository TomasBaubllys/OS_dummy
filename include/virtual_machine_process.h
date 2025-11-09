#ifndef VIRTUAL_MACHINE_H_INCLUDED
#define VIRTUAL_MACHINE_H_INCLUDED

#include "process.h"

typedef enum Virtual_Machine_Steps{
    VIRTUAL_MACHINE_SWITCH_PROCESSOR_TO_USER_MODE,
    VIRTUAL_MACHINE_EXECUTE_USER_PROGRAM,
    VIRTUAL_MACHINE_FREE_RESOURCE_INTERRUPT
} Virtual_Machine_Steps;

class Virtual_Machine_Process: public Process{
    private:
        Virtual_Machine_Steps steps;
    public:
        Virtual_Machine_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Virtual_Machine_Process();
        virtual int8_t execute() override;
};

#endif // VIRTUAL_MACHINE_H_INCLUDED