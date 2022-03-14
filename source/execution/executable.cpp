#include <accelerate/execution/executable.hpp> 

accelerate::execution::executable::executable(executable&  copy) { ::clRetainProgram(copy.__M_exec_handle); }
accelerate::execution::executable::executable(executable&& move)   : __M_exec_handle(move.__M_exec_handle) {  }
accelerate::execution::executable::executable(program& prog)	   : __M_exec_handle(prog.__M_program_handle)
{
	::clRetainProgram(__M_exec_handle);
}

