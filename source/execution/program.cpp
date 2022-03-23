#include <accelerate/execution/program/program.hpp>

accelerate::execution::program::program(program& copy)			: __M_program_handle(copy.__M_program_handle) {  }
accelerate::execution::program::program(program&& move)			: __M_program_handle(move.__M_program_handle) { move.__M_program_handle = nullptr; }
accelerate::execution::program::program(native_handle_type hnd) : __M_program_handle(hnd)					  {  }