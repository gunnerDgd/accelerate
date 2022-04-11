#pragma once
#include <accelerate/device/device.hpp>
#include <accelerate/builder/declare.hpp>
#include <accelerate/execution/declare.hpp>

#include <fstream>

namespace accelerate::execution {
	class program
	{
		template <typename... T> 
		friend class		kernel ;
		friend class build::builder;
	public:
		using			 native_handle_type				   = ::cl_program;
		static constexpr native_handle_type invalid_handle = nullptr	 ;

		program(const program&) ;
		program(const program&&);
	private:
		program(native_handle_type);

	public:
		native_handle_type native_handle() { return __M_program_handle; }

	private:
		native_handle_type __M_program_handle;
	};
}