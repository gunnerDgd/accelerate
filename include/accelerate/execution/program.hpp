#pragma once
#include <accelerate/execution/context.hpp>
#include <accelerate/device/device.hpp>

#include <memory/memory_model.hpp>

namespace accelerate::execution {
	class program
	{
		friend class builder;
		friend class executable;
	public:
		using native_handle_type = ::cl_program;

		class source;
		class binary;

	public:
		template <typename InputIterator>
		static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, source>, program>
			from_source(context&, InputIterator&&, InputIterator&&);

		template <typename InputIterator>
		static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, binary>, program>
			from_binary(context&, InputIterator&&, InputIterator&&);

	private:
		program(native_handle_type);

	public:
		~program();
		program (program&);
		program (program&&);

	private:
		native_handle_type							 __M_program_handle;
		typename device::device::native_handle_type* __M_program_target;
		std::size_t									 __M_program_target_count;
	};

	class program::source
	{
		friend class program;
		friend class builder;
	public:
		source(device::device&, std::string);
		source(device::device&, std::wstring);

		source(source&);
		source(source&&);
		
	private:
		device::device&		  __M_src_target;
		memory::model::io_map __M_src_iomap ;
	};

	class program::binary
	{
		friend class program;
		friend class builder;
	public:
		binary(accelerate::device::device&, std::string) ;
		binary(accelerate::device::device&, std::wstring);

	private:
		device::device::native_handle_type __M_bin_target;
		memory::model::io_map			   __M_bin_iomap ;
	};
}

template <typename InputIterator>
static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, accelerate::execution::program::source>, accelerate::execution::program>
accelerate::execution::program::from_source(context& ctx, InputIterator&& begin, InputIterator&& end)
{
	auto		 src_count  = std::distance(begin, end);
	
	char**		 src_ptr    = new char*										 [src_count];
	std::size_t* src_size   = new std::size_t								 [src_count];
	
	auto*		 src_target = new typename device::device::native_handle_type[src_count];

	for (auto src_idx = 0; begin != end; ++src_idx, ++begin)
	{
		src_ptr   [src_idx] = reinterpret_cast<char*>((*begin).__M_src_iomap .memory_handle().address());
		src_size  [src_idx] =					      (*begin).__M_src_iomap .memory_handle().size   () ;
		src_target[src_idx] =						  (*begin).__M_src_target.native_handle();
	}

	auto src_program =::clCreateProgramWithSource(ctx.native_handle(), src_count, 
												 (const char**)		   src_ptr  , 
												 (const std::size_t*)  src_size , nullptr);

	program src_return(src_program);
			src_return.__M_program_target		= src_target;
			src_return.__M_program_target_count = src_count;
	
	delete[] src_ptr   ;
	delete[] src_size  ;
	delete[] src_target;

	return  src_return;
}

template <typename InputIterator>
static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, accelerate::execution::program::binary>, accelerate::execution::program>
accelerate::execution::program::from_binary(context& ctx, InputIterator&& begin, InputIterator&& end)
{
	auto		 src_count  = std::distance(begin, end);
	
	char**		 src_ptr    = new char*										 [src_count];
	std::size_t* src_size   = new std::size_t								 [src_count];
	
	auto*		 src_target = new typename device::device::native_handle_type[src_count];

	for (auto src_idx = 0; begin != end; ++src_idx, ++begin)
	{
		src_ptr   [src_idx] = reinterpret_cast<char*>((*begin).__M_bin_iomap .memory_handle().address());
		src_size  [src_idx] =					      (*begin).__M_bin_iomap .memory_handle().size   () ;
		src_target[src_idx] =						  (*begin).__M_bin_target;
	}

	auto src_program =::clCreateProgramWithBinary(ctx.native_handle(),  src_count ,
												 (const ::cl_device_id*)src_target,
												 (const std::size_t*)   src_size  ,
												 (const std::uint8_t**) src_ptr   ,
												  nullptr, nullptr);

	program src_return(src_program);
			src_return.__M_program_target		= src_target;
			src_return.__M_program_target_count = src_count;
	
	delete[] src_ptr;
	delete[] src_size;
	delete[] src_target;

	return  src_return;
}