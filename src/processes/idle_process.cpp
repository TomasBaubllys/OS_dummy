#include "../../include/processes/idle_process.h"
#include <iostream>

Idle_Process::Idle_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) :
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::IDLE_PRIORITY),
    do_nothing_counter(0)
{
    this -> saved_registers = {};
}

Idle_Process::~Idle_Process() {

}

Process_State Idle_Process::execute() {
    ++this -> do_nothing_counter;
    // std::cout << "Idle: " << this -> do_nothing_counter << std::endl;
    return Process_State::READY;
}