#include <accelerate/execution/executor.hpp>

accelerate::execution::executor::executor(device::device& dev, context& ctx) 
	: __M_executor_context(ctx),
	  __M_executor_device (dev) { ::clCreateCommandQueue(ctx.native_handle(), dev.native_handle(), 0, nullptr); }

void accelerate::execution::executor::dispatch(task::builtin::read_memory& rdmem)
{
	::clEnqueueReadBuffer(__M_executor_cqueue,
						  rdmem.__M_rd_clmem, true,
						  rdmem.__M_rd_begin,
						  rdmem.__M_rd_size ,
						  rdmem.__M_rd_mem  , 0, nullptr, nullptr);
}

void accelerate::execution::executor::dispatch(task::builtin::write_memory& wrmem)
{
	::clEnqueueWriteBuffer(__M_executor_cqueue,
					 	   wrmem.__M_wr_clmem , true,
						   wrmem.__M_wr_begin ,
						   wrmem.__M_wr_size  ,
						   wrmem.__M_wr_mem   , 0, nullptr, nullptr);
}