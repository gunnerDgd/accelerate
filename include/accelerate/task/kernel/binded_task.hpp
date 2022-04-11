#pragma once
#include <accelerate/task/declare.hpp>
#include <accelerate/memory/memory.hpp>
#include <accelerate/execution/executor.hpp>

namespace accelerate::task {
	template <typename KernelReturn, typename... KernelArgs> 
	class binded<KernelReturn(KernelArgs...)>
	{
	public:
		using native_handle_type = ::cl_kernel;
		using kernel_type		 = execution::kernel<KernelReturn(KernelArgs...)>;
		using executor_type		 = execution::executor;
	public:
		template <typename... InputArgs>
		binded		   (executor_type&, kernel_type&, InputArgs&&...);
		void operator()();

	private:
		template <std::size_t ArgIndex, typename ArgType, typename... Remaining>
		std::enable_if_t<std::is_same_v<memory::device_memory, std::remove_reference_t<ArgType>>>
			__M_init_args(ArgType&&, Remaining&&...);
		template <std::size_t ArgIndex, typename ArgType>
		std::enable_if_t<std::is_same_v<memory::device_memory, std::remove_reference_t<ArgType>>>
			__M_init_args(ArgType&&);

	private:
		executor_type&	   __M_task_executor;
		native_handle_type __M_task_kernel  ;
	};
}

template <typename KernelReturn, typename... KernelArgs>
template <std::size_t ArgIndex, typename ArgType, typename... Remaining>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::remove_reference_t<ArgType>>>
								accelerate::task::binded<KernelReturn(KernelArgs...)>::__M_init_args(ArgType&& args, Remaining&&... remaining)
{
	::clSetKernelArg(__M_task_kernel, ArgIndex, sizeof(ArgType), args.native_handle());
					 __M_init_args<ArgIndex + 1>(std::forward<Remaining>(remaining)...);
}

template <typename KernelReturn, typename... KernelArgs>
template <std::size_t ArgIndex, typename ArgType>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::remove_reference_t<ArgType>>>
								accelerate::task::binded<KernelReturn(KernelArgs...)>::__M_init_args(ArgType&& args)
{
	::clSetKernelArg(__M_task_kernel, ArgIndex, sizeof(ArgType), &args);
}

template <typename KernelReturn, typename... KernelArgs>
template <typename... InputArgs>
accelerate::task::binded<KernelReturn(KernelArgs...)>::binded(executor_type& ctx, kernel_type& kernel, InputArgs&&... args)
	: __M_task_executor(ctx)				  ,
	  __M_task_kernel  (kernel.native_handle())	{ __M_init_args<0>(std::forward<InitArgs>(args)...); }

template <typename KernelReturn, typename... KernelArgs>
void accelerate::task::binded<KernelReturn(KernelArgs...)>::operator()()
{
	__M_task_executor.dispatch()
}