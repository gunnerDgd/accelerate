#pragma once
#include <accelerate/builder/declare.hpp>
#include <accelerate/builder/build_option.hpp>

#include <accelerate/builder/binary.hpp>
#include <accelerate/builder/source.hpp>
#include <accelerate/builder/build_target.hpp>

#include <accelerate/execution/program.hpp>
#include <future>

namespace accelerate::build {
	class builder
	{
	private:
		struct __builder_option							  {};
		struct __sync_build		: public __builder_option {};
		struct __async_build	: public __builder_option {};

	public:
		static inline constexpr __sync_build  sync_build  {};
		static inline constexpr __async_build async_build {};

	public:
		template <typename OptionType>
		std::enable_if_t<std::is_base_of_v<options::intrinsics, OptionType>, builder&> 
			  operator|(OptionType) { return *this; }
		template <typename OptionType>
		std::enable_if_t <std::is_base_of_v<options::preprocessor, OptionType>, builder&>
			  operator|(OptionType);
		template <typename OptionType>
		std::enable_if_t <std::is_base_of_v<options::intrinsics, OptionType>, builder&>
			  operator|(OptionType);
		template <typename OptionType>
		std::enable_if_t <std::is_base_of_v<options::optimization, OptionType>, builder&>
			  operator|(OptionType);
		
	public:
		template <typename BuildOption, typename BuildTarget>
		std::enable_if_t <!std::is_base_of_v<__builder_option, std::remove_reference_t<BuildOption>>>
			operator()() {}

		template <typename BuildTarget>
		std::enable_if_t<std::is_same_v<std::remove_reference_t<BuildTarget>, target>, execution::program>
			operator()(__sync_build, BuildTarget&&);

		template <typename BuildTarget>
		std::enable_if_t<std::is_same_v<std::remove_reference_t<BuildTarget>, target>, std::future<execution::program>>
			operator()(__async_build, BuildTarget&&);

	private:
		std::string __M_builder_option;
	};
}

template <typename OptionType>
std::enable_if_t <std::is_base_of_v<accelerate::build::options::preprocessor, OptionType>, accelerate::build::builder&>
									accelerate::build::builder::operator|(OptionType option)
{
	__M_builder_option += option.to_string();
	return *this;
}

template <typename OptionType>
std::enable_if_t <std::is_base_of_v<accelerate::build::options::intrinsics, OptionType>, accelerate::build::builder&>
									accelerate::build::builder::operator|(OptionType)
{
	__M_builder_option += std::string(OptionType::option);
	return *this;
}

template <typename OptionType>
std::enable_if_t <std::is_base_of_v<accelerate::build::options::optimization, OptionType>, accelerate::build::builder&>
									accelerate::build::builder::operator|(OptionType)
{
	__M_builder_option += std::string(OptionType::option);
	return *this;
}

template <typename BuiltTarget>
std::enable_if_t<std::is_same_v<std::remove_reference_t<BuiltTarget>, accelerate::build::target>, accelerate::execution::program>
																	  accelerate::build::builder::operator()(__sync_build, BuiltTarget&& prog)
{
	auto build_native_handle = new device::device::native_handle_type[prog.__M_program_target_count];
	for(std::size_t i = 0 ; i < prog.__M_program_target_count ; i++)
		 build_native_handle[i] = (prog.__M_program_target)[i]->native_handle();

	::clBuildProgram(prog.__M_program_handle		,
					 prog.__M_program_target_count  ,
					 build_native_handle			,
						  __M_builder_option.c_str(),
					 nullptr,
					 nullptr);

	return program(prog.__M_program_handle);
}

template <typename BuiltTarget>
std::enable_if_t<std::is_same_v<std::remove_reference_t<BuiltTarget>, accelerate::build::target>, std::future<accelerate::execution::program>>
																	  accelerate::build::builder::operator()(__async_build, BuiltTarget&& prog)
{
	return std::async(&builder::operator(), this, async_build, prog);
}