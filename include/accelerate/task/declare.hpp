#pragma once

namespace accelerate::task {
namespace builtin		   {
	class read_memory ;
	class write_memory;
}

namespace kernel {
	template <typename KernelReturn, typename... KernelArgs> class task;
	template <typename ArgumentType>						 class argument;
}
}