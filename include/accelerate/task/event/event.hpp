#pragma once
#include <accelerate/task/declare.hpp>

namespace accelerate::task {
	class event
	{
	public:
		using native_handle_type = ::cl_event;
	public:
		event (native_handle_type);
		~event();

		void			   wait_for		();
		native_handle_type native_handle();

	private:
		native_handle_type __M_event_handle;
	};
}

accelerate::task::event::event (native_handle_type hnd) : __M_event_handle(hnd) { ::clRetainEvent (hnd); }
accelerate::task::event::~event()												{ ::clReleaseEvent(__M_event_handle); }

void accelerate::task::event::wait_for()
{
	::clWaitForEvents(1, &__M_event_handle);
}