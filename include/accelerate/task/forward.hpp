#pragma once
#include <accelerate/task/kernel_task.hpp>
#include <accelerate/task/memory_task.hpp>

namespace accelerate::task {
namespace memory		   {
	template <typename ReadType>
	using read  = basic_task<category::read_operation, ReadType>;
	template <typename WriteType>
	using write = basic_task<category::write_operation, WriteType>;
}
}