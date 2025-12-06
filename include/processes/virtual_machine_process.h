#ifndef VIRTUAL_MACHINE_PROCESS_H_INCLUDED
#define VIRTUAL_MACHINE_PROCESS_H_INCLUDED

#include "process.h"
#include "../../include/virtual_machine.h"

#define VIRTUAL_MACHINE_NAME "Virtual_Machine_Process"

typedef enum Virtual_Machine_Steps{
    VIRTUAL_MACHINE_SWITCH_PROCESSOR_TO_USER_MODE,
    VIRTUAL_MACHINE_EXECUTE_USER_PROGRAM,
    VIRTUAL_MACHINE_FREE_RESOURCE_INTERRUPT
} Virtual_Machine_Steps;

class Virtual_Machine_Process: public Process{
    private:
        Virtual_Machine_Steps step;
        Virtual_Machine* vm;
    public:
        Virtual_Machine_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Virtual_Machine_Process();
        Process_State execute() override;
};

#endif // VIRTUAL_MACHINE_PROCESS_H_INCLUDED