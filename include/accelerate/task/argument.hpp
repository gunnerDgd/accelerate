#pragma once
#include <type_traits>

#include <accelerate/memory/mapped/read_only.hpp>
#include <accelerate/memory/unmapped/read_only.hpp>

namespace accelerate::execution {
	template <typename ArgumentType>
	class argument
	{
	public:
		template <typename InputType>
		argument(InputType&&);
#ifdef __cplusplus >= 20200000L
		template <typename InputType>
		argument(InputType&&) requires std::is_same_v<std::remove_cvref_t<InputType>, ArgumentType>
#endif

	public:

	private:
		
	};
}

template <typename ArgumentType>
template <typename InputType>
accelerate::execution::argument<ArgumentType>::argument(InputType&&)
{
	static_assert(!std::is_scalar_v<ArgumentType>, "[Execution][Argument] Error :: Non - Scalar Type Inserted.");

	
}