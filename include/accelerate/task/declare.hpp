#pragma once
#include <CL/cl.hpp>

#include <accelerate/execution/kernel.hpp>
#include <accelerate/memory/memory.hpp>

namespace accelerate::task {
															 class event ;
	template <typename KernelReturn, typename... KernelArgs> class binded;
	template <typename KernelReturn, typename... KernelArgs> class await ;
}