#pragma once
#include <accelerate/execution/context.hpp>

#include <accelerate/task/builtin/memory/memory_task.hpp>
#include <accelerate/task/kernel/kernel_task.hpp>

namespace accelerate::execution {
	class executor
	{
	public:
		using native_handle_type  = ::cl_command_queue;
		using native_context_type = execution::context;
		class event;

	public:
		void dispatch(task::builtin::read_memory &);
		void dispatch(task::builtin::write_memory&);
	public:
		template <typename KernelType>
		void dispatch(KernelType&&);

	public:
		native_context_type& get_context  () { return __M_executor_context; }
		native_handle_type   native_handle() { return __M_executor_cqueue ; }

	private:
		native_handle_type  __M_executor_cqueue ;
		execution::context& __M_executor_context;
	};
}

template <typename KernelType>
void accelerate::execution::executor::dispatch(KernelType&& kernel)
{
	kernel.			__M_set_argument<0>() ;
	::clEnqueueTask(__M_executor_cqueue	  ,
					kernel.__M_task_kernel,
					0, nullptr, nullptr)  ;
}