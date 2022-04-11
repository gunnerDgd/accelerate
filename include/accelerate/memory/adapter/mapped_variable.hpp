#pragma once
#pragma once
#include <accelerate/memory/utility.hpp>

namespace accelerate::memory::adapter {
	template <typename VariableType>
	class mapped_variable : protected mapped<std::conditional_t<std::is_array_v<VariableType>, 
													 			std::decay_t   <VariableType>,
																  			    VariableType>,
															   (std::is_array_v<VariableType>) ? std::extent_v<VariableType>
																							   : 1>
	{
	public:
		using value_type = VariableType;
		using reference  = VariableType&;
		using pointer    = VariableType*;

	public:
		template <typename InputVariable>
		mapped_variable(InputVariable&&);
		mapped_variable() {}

	public:
		template <typename CastType>
		operator CastType();
		
		template <typename InputType>
		std::enable_if_t<std::is_same_v<value_type, std::decay_t<InputType>>, mapped_variable>
			operator=(InputType&&);
	};

	template <typename VariableType>
	mapped_variable(VariableType&&)->mapped_variable<std::decay_t<VariableType>>;
}

template <typename VariableType>
template <typename InputVariable>
accelerate::memory::adapter::mapped_variable<VariableType>::mapped_variable(InputVariable&& init)
	: mapped()
{
	write_to(*this, init);
}

template <typename VariableType>
template <typename CastType>
accelerate::memory::adapter::mapped_variable<VariableType>::operator CastType()
{
	value_type		 cast_original ;
	read_from(*this, cast_original);
	
	return reinterpret_cast<CastType>(cast_original);
}

template <typename VariableType>
template <typename InputType>
std::enable_if_t<std::is_same_v<typename accelerate::memory::adapter::mapped_variable<VariableType>::value_type,
				 std::decay_t<InputType>>, accelerate::memory::adapter::mapped_variable<VariableType>>
	accelerate::memory::adapter::mapped_variable<VariableType>::operator=(InputType&& input)
{
	write_to(*this, input);
}