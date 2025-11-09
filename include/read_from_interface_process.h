#ifndef READ_FROM_INTERFACE_H_INCLUDED
#define READ_FROM_INTERFACE_H_INCLUDED

#include "process.h"

typedef enum Read_From_Interface_Process_Steps{
    READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_FROM_USER_INTERFACE,
    READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_F$,
    READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_HARD_DISK,
    READ_FROM_INTERFACE_CHECK_IF_FILE_EXISTS,
    READ_FROM_INTERFACE_READ_AND_DIVIDE_FILE,
    READ_FROM_INTERFACE_BLOCKED_WAITING_FOR_SUPERVISOR_MEMORY,
    READ_FROM_INTERFACE_COPY_BYTES_TO_SUPERVISOR_MEMORY,
    READ_FROM_INTERFACE_RELEASE_TASK_IN_SUPERVISOR,
    READ_FROM_INTERFACE_CHECK_IF_INPUT_STARTS_WITH_$,
    READ_FROM_INTERFACE_RELEASE_SYSTEM_COMMAND
} Read_From_Interface_Process_Steps;

class Read_From_Interface_Process: public Process{
    private:
        Read_From_Interface_Process_Steps steps;
    public:
        Read_From_Interface_Process(Saved_Registers saved_registers, uint16_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
        ~Read_From_Interface_Process();
        virtual int8_t execute() override;

};


#endif // READ_FROM_INTERFACE_H_INCLUDED