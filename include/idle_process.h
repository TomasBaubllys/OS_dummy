#ifndef IDLE_PROCESS_H_INCLUDED
#define IDLE_PROCESS_H_INCLUDED
#include "process.h"

class Idle_Process: public Process{
    private:
        uint64_t do_nothing_counter;
	public:
		Idle_Process(Saved_Registers saved_registers, uint32_t unique_id, Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
		~Idle_Process();

		virtual Process_State execute() override;
};

#endif // IDLE_PROCESS_H_INLCUDED