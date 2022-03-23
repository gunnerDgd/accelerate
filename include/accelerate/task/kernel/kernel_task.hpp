#pragma once
#include <accelerate/task/declare.hpp>
#include <accelerate/task/kernel/argument.hpp>

#include <accelerate/execution/declare.hpp>
#include <accelerate/execution/kernel.hpp>

namespace accelerate::task::kernel {
	template <typename KernelReturn, typename... KernelArgs> 
	class task<KernelReturn(KernelArgs...)>
	{
		friend class execution::executor;
	public:
		using native_handle_type = ::cl_kernel;
		using kernel_type		 = execution::kernel<KernelReturn(KernelArgs...)>;
		using context_type		 = execution::context;
		using argument_type      = std::tuple<argument<std::remove_reference_t<KernelArgs>>...>;
	public:
		template <typename... InputArgs>
		task (context_type&, kernel_type&, InputArgs&&...);
		~task();

	private:
		context_type&	   __M_task_context ;
		argument_type      __M_task_argument;
		native_handle_type __M_task_kernel  ;

		template <std::size_t I>
		std::enable_if_t<I == sizeof...(KernelArgs)> __M_set_argument(argument_type&);
		template <std::size_t I>
		std::enable_if_t<I  < sizeof...(KernelArgs)> __M_set_argument(argument_type&);
	};
}

template <typename KernelReturn, typename... KernelArgs>
template <typename... InputArgs>
accelerate::task::kernel::task<KernelReturn(KernelArgs...)>::task(context_type& ctx, kernel_type& kernel, InputArgs&&... args)
	: __M_task_context (ctx)						,
	  __M_task_kernel  (kernel.native_handle())	    ,
	  __M_task_argument(make_argument(ctx, args...))  {  }

template <typename KernelReturn, typename... KernelArgs>
template <std::size_t I>
std::enable_if_t<I == sizeof...(KernelArgs)> 
	accelerate::task::kernel::task<KernelReturn(KernelArgs...)>::__M_set_argument(argument_type& args) {  }

template <typename KernelReturn, typename... KernelArgs>
template <std::size_t I>
std::enable_if_t <I  < sizeof...(KernelArgs)> 
	accelerate::task::kernel::task<KernelReturn(KernelArgs...)>::__M_set_argument(argument_type& args)
{
	auto& arg_set  =		std::get<I>(args);
	auto  arg_size = sizeof(std::remove_reference_t<decltype(arg_set)>::argument_type);

	::clSetKernelArg	   (__M_task_kernel, I, arg_size, (const void*)&arg_set);
	__M_set_argument<I + 1>(args);
}