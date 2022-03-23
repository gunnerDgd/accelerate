#pragma once
#include <accelerate/execution/program/program.hpp>
#include <type_traits>

namespace accelerate::execution {
	template <typename ReturnType, typename... ArgumentType>
	class kernel<ReturnType(ArgumentType...)>
	{
		friend class builder;
		friend class executor;
	public:
		using native_handle_type = ::cl_kernel;
		kernel (program&, std::string);
		~kernel();
		
		kernel (kernel&);
		kernel (kernel&&);

		native_handle_type native_handle() { return __M_kernel_handle; }

	private:
		native_handle_type __M_kernel_handle;
	};
}

template <typename ReturnType, typename... ArgumentType>
accelerate::execution::kernel<ReturnType(ArgumentType...)>::kernel(program& exec, std::string name)
{
	__M_kernel_handle = ::clCreateKernel(exec.__M_program_handle, name.c_str(), nullptr);
					    ::clRetainKernel(__M_kernel_handle);
}

template <typename ReturnType, typename... ArgumentType>
accelerate::execution::kernel<ReturnType(ArgumentType...)>::~kernel() { ::clReleaseKernel(__M_kernel_handle); }

template <typename ReturnType, typename... ArgumentType>
accelerate::execution::kernel<ReturnType(ArgumentType...)>::kernel(kernel& copy)  
	: __M_kernel_handle(copy.__M_kernel_handle) { ::clRetainKernel(__M_kernel_handle); }

template <typename ReturnType, typename... ArgumentType>
accelerate::execution::kernel<ReturnType(ArgumentType...)>::kernel(kernel&& move) 
	: __M_kernel_handle(move.__M_kernel_handle) {  }