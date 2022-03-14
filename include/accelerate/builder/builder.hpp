#pragma once
#include <accelerate/builder/build_option.hpp>

#include <accelerate/execution/program.hpp>
#include <accelerate/execution/executable.hpp>

namespace accelerate::execution {
	class builder
	{
	public:
		template <typename OptionType>
		auto& operator|(OptionType&&) { return *this; }
		template <typename OptionType>
		std::enable_if_t <std::is_base_of_v<build_option::preprocessor, OptionType>, builder&>
			  operator|(OptionType);
		template <typename OptionType>
		std::enable_if_t <std::is_base_of_v<build_option::intrinsics, OptionType>, builder&>
			  operator|(OptionType);
		template <typename OptionType>
		std::enable_if_t <std::is_base_of_v<build_option::optimization, OptionType>, builder&>
			  operator|(OptionType);
		
	public:
		template <typename ProgramType>
		std::enable_if_t<std::is_same_v<ProgramType, program>, executable>
			operator()(ProgramType&&);

	private:
		std::string __M_builder_option;
	};
}

template <typename OptionType>
std::enable_if_t <std::is_base_of_v<accelerate::execution::build_option::preprocessor, OptionType>, accelerate::execution::builder&>
									accelerate::execution::builder::operator|(OptionType option)
{
	__M_builder_option += option.to_string();
	return *this;
}

template <typename OptionType>
std::enable_if_t <std::is_base_of_v<accelerate::execution::build_option::intrinsics, OptionType>, accelerate::execution::builder&>
									accelerate::execution::builder::operator|(OptionType)
{
	__M_builder_option += std::string(OptionType::option);
	return *this;
}

template <typename OptionType>
std::enable_if_t <std::is_base_of_v<accelerate::execution::build_option::optimization, OptionType>, accelerate::execution::builder&>
									accelerate::execution::builder::operator|(OptionType)
{
	__M_builder_option += std::string(OptionType::option);
	return *this;
}

template <typename ProgramType>
std::enable_if_t<std::is_same_v<ProgramType, accelerate::execution::program>, accelerate::execution::executable>
accelerate::execution::builder::operator()(ProgramType&& prog)
{
	::clBuildProgram(prog.__M_program_handle, 
					 prog.__M_program_target_count,
					 prog.__M_program_target	 ,
						  __M_builder_option.c_str(),
					 nullptr,
					 nullptr);

	return 
}