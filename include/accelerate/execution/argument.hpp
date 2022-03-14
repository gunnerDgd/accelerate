#pragma once
#include <CL/cl.h>
#include <type_traits>

namespace accelerate::execution {
	template <typename ArgumentType>
	class argument
	{
	public:
		template <typename InputType>
		argument(InputType&&);

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