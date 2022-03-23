#pragma once
#include <tuple>
#include <type_traits>

#include <accelerate/task/declare.hpp>

#include <accelerate/memory/mapped/mapped.hpp>
#include <accelerate/memory/unmapped/unmapped.hpp>

namespace accelerate::task::kernel {
	template <typename ArgumentType> 
	class argument
	{
		template <typename R, typename... T> 
		friend class task;
	public:
		using argument_type = std::remove_reference_t<ArgumentType>;
		using memory_type   = accelerate::memory::unmapped;
	public:
		template <typename InputArgument>
		argument (execution::context&, InputArgument&&);
		~argument()									   {  }

	private:
		memory_type   __M_arg_memory  ;
		argument_type __M_arg_argument;
	};

	template <typename ArgumentType> 
	class argument<ArgumentType*>
	{
		template <typename R, typename... T> 
		friend class task;
	public:
		using argument_type = ArgumentType* ;
		using memory_type   = memory::mapped;

	public:
		argument (execution::context&, argument_type);
		~argument()									 {  }

	private:
		memory_type   __M_arg_memory;
		argument_type __M_arg_argument;
	};

	template <typename... InputArgument>
	std::tuple<argument<std::remove_reference_t<InputArgument>>...> 
		make_argument(execution::context&, InputArgument&&...);
}

template <typename... InputArgument>
std::tuple<accelerate::task::kernel::argument<std::remove_reference_t<InputArgument>>...>
		   accelerate::task::kernel::make_argument(execution::context& ctx, InputArgument&&... args)
{
	return std::tuple<argument<std::remove_reference_t<InputArgument>>...> 
		{ ((argument<std::remove_reference_t<InputArgument>>(args)), ...) };
}

template <typename ArgumentType>
template <typename InputArgument>
accelerate::task::kernel::argument<ArgumentType>::argument(execution::context& ctx, InputArgument&& arg)
	: __M_arg_argument(arg),
	  __M_arg_memory  (ctx.native_handle(), accelerate::memory::all, sizeof(InputArgument)) {  }

template <typename ArgumentType>
accelerate::task::kernel::argument<ArgumentType*>::argument(execution::context& ctx, argument_type arg)
	: __M_arg_memory  (ctx.native_handle(), accelerate::memory::all, arg),
      __M_arg_argument(arg)												 {  }