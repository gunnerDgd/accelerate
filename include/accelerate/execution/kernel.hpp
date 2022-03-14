#pragma once
#include <accelerate/execution/executable.hpp>
#include <type_traits>

namespace accelerate::execution {
	template <typename... T>
	class kernel;

	template <typename ReturnType, typename... ArgumentType>
	class kernel<ReturnType(ArgumentType...)>
	{
		friend class builder;
	public:
		using native_handle_type = ::cl_kernel;
		kernel (executable&, std::string);
		~kernel();
		
		kernel (kernel&);
		kernel (kernel&&);

	public:
		template <typename... InputArgs>
		void operator()(InputArgs&&...);

	private:
		native_handle_type __M_kernel_handle;
	};
}

template <typename ReturnType, typename... ArgumentType>
accelerate::execution::kernel<ReturnType(ArgumentType...)>::kernel(executable& exec, std::string name)
{
	__M_kernel_handle = ::clCreateKernel(exec.__M_exec_handle, name.c_str(), nullptr);
}

template <typename ReturnType, typename... ArgumentType>
template <typename... InputArgs>
void accelerate::execution::kernel<ReturnType(ArgumentType...)>::operator()(InputArgs&&... args)
{
}