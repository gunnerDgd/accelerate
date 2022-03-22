#pragma once
#include <accelerate/execution/execution_traits.hpp>
#include <accelerate/execution/declare.hpp>

#include <accelerate/task/builtin/memory/memory_task.hpp>

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
		

	public:
		native_context_type& get_context  () { return __M_executor_context; }
		native_handle_type   native_handle() { return __M_executor_cqueue ; }

	private:
		native_handle_type  __M_executor_cqueue ;
		execution::context& __M_executor_context;
	};
}