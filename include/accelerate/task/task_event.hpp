#pragma once
#include <CL/cl.h>

namespace accelerate::task {
	class event
	{
		event(::cl_event);
	public:
		using native_handle_type = ::cl_event;
		event(event&)  = default;
		event(event&&) = default;

	public:
		void wait_for();
	};
}