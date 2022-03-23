#include <accelerate/execution/program/build_target.hpp> 

accelerate::execution::build_target::build_target(build_target&  copy) 
	: __M_program_handle	  (copy.__M_program_handle),
	  __M_program_target	  (copy.__M_program_target),
	  __M_program_target_count(copy.__M_program_target_count) { ::clRetainProgram(copy.__M_program_handle); }
 
accelerate::execution::build_target::build_target(build_target&& move) 
	: __M_program_handle	  (move.__M_program_handle),
	  __M_program_target	  (move.__M_program_target),
	  __M_program_target_count(move.__M_program_target_count) 
{
	move.__M_program_handle		  = nullptr;
	move.__M_program_target		  = nullptr;
	move.__M_program_target_count = 0;
}

accelerate::execution::build_target::build_target(native_handle_type hnd, std::size_t* hnd_size, device::device** dev_list, std::size_t dev_count)
	: __M_program_handle	  (hnd)		 ,
	  __M_program_size		  (hnd_size) ,
	  __M_program_target	  (dev_list) ,
	  __M_program_target_count(dev_count) { ::clRetainProgram(__M_program_handle); }

accelerate::execution::build_target::~build_target()
{
	delete[] __M_program_size  ;
	delete[] __M_program_target;
}