#ifndef IDLE_PROCESS_H_INCLUDED
#define IDLE_PROCESS_H_INCLUDED
#include "process.h"

typedef enum Idle_Process_Steps {
    // ???????
    IDLE_PROCESS_ON,
    IDLE_PROCESS_OFF
} Idle_Process_Steps;


class Idle_Process: public Process{
    private:
        Idle_Process_Steps steps;
    
	public:
		Idle_Process(Saved_Registers saved_registers, uint32_t unique_id, Kernel* kernel, CPU* cpu, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
		~Idle_Process();

		virtual int8_t execute() override;
};



#endif // IDLE_PROCESS_H_INLCUDED