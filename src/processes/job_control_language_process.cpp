#include "../../include/processes/job_control_language_process.h"
#include "../../include/kernel.h"
#include <stdexcept>
#include <iostream>

Job_Control_Language_Process::Job_Control_Language_Process(Kernel* kernel, Process* parent_process, std::vector<Process*> friend_processes, std::string username) : 
    Process(kernel, parent_process, friend_processes, username, Process_Priorities::JOB_CONTROL_LANGUAGE_PRIORITY){
    this -> name = JCL_NAME;
} 

Job_Control_Language_Process::~Job_Control_Language_Process(){

}

Process_State Job_Control_Language_Process::execute(){
    switch (this -> step){
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_BLOCKED_WAIT_FOR_TASK_IN_SUPERVISOR:
            std::cout << "JCL here" << std::endl;
            if(this -> owns_resource(Resource_Type::TASK_IN_SUPERVISOR)) {
                this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_INITIALIZE_PROGRAM_LIST;
                return Process_State::READY;
            }

            this -> kernel -> request_resource(this, Resource_Type::TASK_IN_SUPERVISOR);
            return Process_State::BLOCKED;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_INITIALIZE_PROGRAM_LIST:
            // empty?
            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_TAKE_BLOCK_FROM_SUPERVISOR_MEMORY_1;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_TAKE_BLOCK_FROM_SUPERVISOR_MEMORY_1:
            static Memory* mem = this -> kernel -> get_memory();

            if(!mem){
                throw std::runtime_error("no mem");
            }
            // first page
            static uint32_t cur_page_index = MEM_SUPERVISOR_PAGE_BEGIN * MEM_PAGE_SIZE;
            //static uint32_t* cur_page = &mem -> memory[MEM_SUPERVISOR_PAGE_BEGIN * MEM_PAGE_SIZE];
            
            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_LOS;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_LOS:
            if(mem -> memory[cur_page_index] == MEM_PROGRAM_LOS_UINT32){
                this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_ATTACH_BLOCK_TO_PROGRAM_LIST;
                return Process_State::READY;
            }
            
            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_LOS_NOT_FOUND;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_ATTACH_BLOCK_TO_PROGRAM_LIST:
            //empty?
            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_TAKE_BLOCK_FROM_SUPERVISOR_MEMORY_2;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_TAKE_BLOCK_FROM_SUPERVISOR_MEMORY_2:
            cur_page_index += MEM_PAGE_SIZE;

            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_BYE_OR_IS_IT_LAST_BLOCK;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_BYE_OR_IS_IT_LAST_BLOCK:
            if(mem -> memory[cur_page_index] == MEM_PROGRAM_BYE_UINT32 || cur_page_index >= MEM_SUPERVISOR_PAGE_END * MEM_PAGE_SIZE){
                this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_BYE;
                return Process_State::READY;
            }

            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_TAKE_BLOCK_FROM_SUPERVISOR_MEMORY_2;
            return Process_State::READY;
            
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_CHECK_IF_BLOCK_IS_BYE:
            if(mem -> memory[cur_page_index] == MEM_PROGRAM_BYE_UINT32){
                this -> step == Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_ATTACH_BOCK_TO_PROGRAM_LIST_AND_CREATE_RESOURCE_LOADER_PACKAGE;
                return Process_State::READY;
            }

            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_BYE_NOT_FOUND;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_ATTACH_BOCK_TO_PROGRAM_LIST_AND_CREATE_RESOURCE_LOADER_PACKAGE:
            // nothing for the attaching
        
            this -> kernel -> init_resource(Resource_Type::LOADER_PACKAGE, this);

            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_PIE_IN_THE_OVEN;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_PIE_IN_THE_OVEN:
            this -> kernel -> release_resource(Resource_Type::PIE_IN_THE_OVEN);

            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_SYSTEM_COMMAND;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_BYE_NOT_FOUND:
            this -> kernel -> release_resource(Resource_Type::STRING_IN_MEMORY, JOB_CONTROL_LANGUAGE_PROCESS_MSG_BYE_NOT_FOUND);

            this -> kernel -> release_resource(Resource_Type::SUPERVISOR_MEMORY);
            this -> return_owned_resources();
            
            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_BLOCKED_WAIT_FOR_TASK_IN_SUPERVISOR;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_STRING_IN_MEMORY_WITH_INFO_LOS_NOT_FOUND:
            this -> kernel -> release_resource(Resource_Type::STRING_IN_MEMORY, JOB_CONTROL_LANGUAGE_PROCESS_MSG_BYE_NOT_FOUND);

            this -> kernel -> release_resource(Resource_Type::SUPERVISOR_MEMORY);
            this -> return_owned_resources();

            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_BLOCKED_WAIT_FOR_TASK_IN_SUPERVISOR;
            return Process_State::READY;
            break;
        case Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_FREE_RESOURCE_SYSTEM_COMMAND:
            this -> kernel -> release_resource(Resource_Type::SYSTEM_COMMAND);


            this -> step = Job_Control_Language_Process_Steps::JOB_CONTROL_LANGUAGE_PROCESS_BLOCKED_WAIT_FOR_TASK_IN_SUPERVISOR;
            return Process_State::READY;

            break;
        
        default:
            break;
    }

    return Process_State::BLOCKED_STOPPED;
}