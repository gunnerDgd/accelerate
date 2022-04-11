#pragma once
#include <accelerate/task/declare.hpp>

namespace accelerate::task {
	template <typename KernelReturn, typename... KernelArgs>
	class await<KernelReturn(KernelArgs...)>
	{
	public:
		using native_handle_type = ::cl_kernel;
		using kernel_type		 = execution::kernel<KernelReturn(KernelArgs...)>;
		using context_type		 = execution::context::native_handle_type;

	public:
		template <typename... InitArgs>
		await(execution::context&, InitArgs&&...);

	private:
		template <std::size_t ArgIndex, typename ArgType, typename... Remaining>
		std::enable_if_t<std::is_same_v<memory::device_memory, std::remove_reference_t<ArgType>>>
			__M_init_args(ArgType&&, Remaining&&...);
		template <std::size_t ArgIndex, typename ArgType>
		std::enable_if_t<std::is_same_v<memory::device_memory, std::remove_reference_t<ArgType>>>
			__M_init_args(ArgType&&);

	private:
		context_type	   __M_await_context;
		native_handle_type __M_await_handle ;
	};
}

template <typename KernelReturn, typename... KernelArgs>
template <std::size_t ArgIndex, typename ArgType, typename... Remaining>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::remove_reference_t<ArgType>>>
								accelerate::task::await<KernelReturn(KernelArgs...)>::__M_init_args(ArgType&& args, Remaining&&... remaining)
{
	::clSetKernelArg(__M_task_kernel, ArgIndex, sizeof(ArgType), args.native_handle());
					 __M_init_args<ArgIndex + 1>(std::forward<Remaining>(remaining)...);
}

template <typename KernelReturn, typename... KernelArgs>
template <std::size_t ArgIndex, typename ArgType>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::remove_reference_t<ArgType>>>
								accelerate::task::await<KernelReturn(KernelArgs...)>::__M_init_args(ArgType&& args)
{
	::clSetKernelArg(__M_task_kernel, ArgIndex, sizeof(ArgType), &args);
}

template <typename KernelReturn, typename... KernelArgs>
template <typename... InitArgs>
accelerate::task::await<KernelReturn(KernelArgs...)>::await(execution::context& context, InitArgs&&... args)
	: __M_await_context(context.native_handle())
{
	__M_init_args<0>(std::forward<InitArgs>(args)...);
}