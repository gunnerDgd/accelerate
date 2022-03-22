#pragma once
#include <accelerate/device/device.hpp>
#include <accelerate/execution/context.hpp>

namespace accelerate::queueing {
	class command_queue
	{
	public:
		using native_handle_type = ::cl_command_queue;
		
	public:
		command_queue (device::device&, execution::context&);
		~command_queue();
		
		command_queue (command_queue&);
		command_queue (command_queue&&);

	private:
		native_handle_type __M_cqueue_handle;
	};
}