#include <accelerate/queueing/command_queue.hpp>

accelerate::queueing::command_queue::command_queue(device::device& dev, execution::context& ctx)
	: __M_cqueue_handle(::clCreateCommandQueue(ctx.native_handle(), dev.native_handle(), 0, nullptr)) 
{
	::clRetainCommandQueue(__M_cqueue_handle);
}

accelerate::queueing::command_queue::~command_queue() { ::clReleaseCommandQueue(__M_cqueue_handle); }
accelerate::queueing::command_queue::command_queue(command_queue&  copy) : __M_cqueue_handle(copy.__M_cqueue_handle)
{
	::clRetainCommandQueue(__M_cqueue_handle);
}
accelerate::queueing::command_queue::command_queue(command_queue&& move) : __M_cqueue_handle(move.__M_cqueue_handle) {  }

