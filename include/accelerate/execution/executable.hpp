#pragma once
#include <accelerate/execution/program.hpp>
#include <fstream>

namespace accelerate::execution {
	class executable
	{
	public:
		using native_handle_type = ::cl_program;

		executable(executable&);
		executable(executable&&);
	private:
		executable(program&);
	public:
		void export_to(std::ofstream&);

	private:
		native_handle_type __M_exec_handle;
	};
}

