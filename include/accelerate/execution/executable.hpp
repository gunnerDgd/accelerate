#pragma once
#include <accelerate/execution/program.hpp>

namespace accelerate::execution {
	class executable
	{
	public:
		using native_handle_type = ::cl_program;

		executable(executable&);
		executable(executable&&);
	private:
		executable(program&);

	private:
		native_handle_type __M_exec_handle;
	};
}

