#pragma once
#include <accelerate/device/device.hpp>
#include <fstream>

namespace accelerate::execution {
	class program
	{
		template <typename... T> class kernel;
	public:
		using native_handle_type = ::cl_program;

		program(program&) ;
		program(program&&);
	private:
		program(native_handle_type);

	public:
		native_handle_type native_handle() { return __M_program_handle; }

	private:
		native_handle_type __M_program_handle	   ;
	};
}