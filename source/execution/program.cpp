#include <accelerate/execution/program.hpp>

accelerate::execution::program::binary::binary(device::device& dev, std::string path) : __M_bin_target(dev.native_handle()),
																						__M_bin_iomap (path, memory::io_map::all_file) {  }

accelerate::execution::program::binary::binary(device::device& dev, std::wstring path) : __M_bin_target(dev.native_handle()),
																						 __M_bin_iomap (path, memory::io_map::all_file) {  }

accelerate::execution::program::~program()
{
	::clReleaseProgram(__M_program_handle);
}

accelerate::execution::program::program(program&& move) : __M_program_handle(move.__M_program_handle) {  }
accelerate::execution::program::program(program&  copy) : __M_program_handle(copy.__M_program_handle)
{
	::clRetainProgram(__M_program_handle);
}

accelerate::execution::program::program(native_handle_type hnd) : __M_program_handle(hnd)
{
	::clBuildProgram()
}

accelerate::execution::program::source::source(device::device& target, std::string path) : __M_src_iomap (path, memory::io_map::all_file),
																						   __M_src_target(target)						 {  }

accelerate::execution::program::source::source(device::device& target, std::wstring path) : __M_src_iomap (path, memory::io_map::all_file),
																						    __M_src_target(target)						 {  }
accelerate::execution::program::source::source(source& copy) : __M_src_iomap (copy.__M_src_iomap),
															   __M_src_target(copy.__M_src_target) {  }

accelerate::execution::program::source::source(source&& move): __M_src_iomap (std::move(move.__M_src_iomap)),
															   __M_src_target(move.__M_src_target)			{  }