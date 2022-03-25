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
		template <typename R, typename... T> friend class task;
	public:
		using argument_type = std::remove_reference_t<ArgumentType>;
		using memory_type   =		   memory::unmapped;
		using size_type		= typename memory::unmapped::size_type;
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
		template <typename R, typename... T> friend class task;
	public:
		using argument_type = ArgumentType* ;
		using memory_type   =		   memory::mapped;
		using size_type     = typename memory::mapped::size_type;

	public:
		template <std::size_t InputCount>
		argument (execution::context&, ArgumentType(&)[InputCount]);
		argument (execution::context&, argument_type, size_type);
		~argument()													{  }

	private:
		memory_type   __M_arg_memory	 ;
		size_type	  __M_arg_memory_size;
		argument_type __M_arg_argument   ;
	};
}

template <typename ArgumentType>
template <typename InputArgument>
accelerate::task::kernel::argument<ArgumentType>::argument(execution::context& ctx, InputArgument&& arg)
	: __M_arg_argument   (arg),
	  __M_arg_memory     (ctx, accelerate::memory::all, sizeof(InputArgument)) {  }

template <typename ArgumentType>
template <std::size_t InputCount>
accelerate::task::kernel::argument<ArgumentType*>::argument(execution::context& ctx, ArgumentType(&arg)[InputCount])
	: __M_arg_memory     (ctx, accelerate::memory::all, arg),
      __M_arg_argument   ((argument_type)arg)				,
	  __M_arg_memory_size(sizeof(ArgumentType) * InputCount){  }

template <typename ArgumentType>
accelerate::task::kernel::argument<ArgumentType*>::argument(execution::context& ctx, argument_type arg_pointer, size_type arg_size)
	: __M_arg_memory	 (ctx, accelerate::memory::all, arg_pointer, arg_size),
      __M_arg_argument   (arg_pointer)										  ,
	  __M_arg_memory_size(arg_size)											  {  }