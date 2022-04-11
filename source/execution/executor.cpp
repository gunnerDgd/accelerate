#include <accelerate/execution/executor.hpp>

accelerate::execution::executor::executor(device::device& dev, context& ctx) 
	: __M_executor_context(ctx),
	  __M_executor_device (dev) { ::clCreateCommandQueue(ctx.native_handle(), dev.native_handle(), 0, nullptr); }

typename accelerate::execution::executor::context_type& 
		 accelerate::execution::executor::get_context  () { return __M_executor_context; }

typename accelerate::execution::executor::native_handle_type   
		 accelerate::execution::executor::native_handle() { return __M_executor_cqueue; }