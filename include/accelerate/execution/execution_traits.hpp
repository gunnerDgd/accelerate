#pragma once
#include <accelerate/execution/kernel.hpp>

namespace accelerate::execution::category {

	template <typename... T>
	struct is_kernel_type									   { static constexpr bool value = false; };

	template <typename KernelReturn, typename... KernelArgs>
	struct is_kernel_type<kernel<KernelReturn(KernelArgs...)>> { static constexpr bool value = true ; };

	template <typename... T>
	inline constexpr bool is_kernel_type_v = is_kernel_type<T...>::value;

	struct dispatch_category {};
	struct memory_operation : public dispatch_category {};
	struct read_memory		: public memory_operation  {};
	struct write_memory		: public memory_operation  {};
}