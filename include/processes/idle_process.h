#ifndef IDLE_PROCESS_H_INCLUDED
#define IDLE_PROCESS_H_INCLUDED
#include "process.h"

#define IDLE_NAME "Idle_Process"

class Idle_Process: public Process{
    private:
        uint64_t do_nothing_counter;
	public:
		Idle_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username);
		~Idle_Process();

		Process_State execute() override;
};

#endif // IDLE_PROCESS_H_INLCUDED