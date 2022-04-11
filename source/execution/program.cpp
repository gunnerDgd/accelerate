#include <accelerate/execution/program.hpp>

accelerate::execution::program::program(const program& copy)		  : __M_program_handle(copy.__M_program_handle) {  }
accelerate::execution::program::program(const program&& move)		  : __M_program_handle(move.__M_program_handle) {  }
accelerate::execution::program::program(const native_handle_type hnd) : __M_program_handle(hnd)					    {  }