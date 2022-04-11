#pragma once
#include <accelerate/execution/context.hpp>
#include <accelerate/device/device.hpp>

namespace accelerate::execution {
	class executor
	{
	public:
		using native_handle_type = ::cl_command_queue;
		using context_type		 = execution::context;
		
	public:
		executor (device::device&, context&);
		~executor() {}
	public:
		template <typename KernelType>
		void dispatch(KernelType&&);

	public:
		context_type&      get_context  ();
		native_handle_type native_handle();

	private:
		native_handle_type __M_executor_cqueue ;
		context_type      &__M_executor_context;
		device::device&	   __M_executor_device ;
	};
}

template <typename KernelType>
void accelerate::execution::executor::dispatch(KernelType&& kernel)
{
	kernel.			__M_set_argument<0>(kernel.__M_task_argument);
	::clEnqueueTask(__M_executor_cqueue	  ,
					kernel.__M_task_kernel,
					0, nullptr, nullptr)  ;
}