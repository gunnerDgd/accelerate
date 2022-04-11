#pragma once
#include <tuple>
#include <type_traits>

#include <accelerate/execution/executor.hpp>
#include <accelerate/memory/mapped/mapped.hpp>

namespace accelerate::task::argument {
	template <typename ArgumentType>
	class mapped
	{
	public:
		using value_type = ArgumentType;
		using pointer	 = ArgumentType*;
		using reference  = ArgumentType&;

	public:
		mapped(execution::executor&, reference);
		mapped(execution::executor&, pointer, memory::types::size_type);

	private:
		memory::mapped<ArgumentType> __M_argument_memory;
	};
}

template <typename ArgumentType>
accelerate::task::argument::mapped<ArgumentType>::mapped(execution::executor& exec, reference map_ref)
	: __M_argument_memory(exec, map_ref)
{

}

template <typename ArgumentType>
accelerate::task::argument::mapped<ArgumentType>::mapped(execution::executor&, pointer, memory::types::size_type size)
{

}