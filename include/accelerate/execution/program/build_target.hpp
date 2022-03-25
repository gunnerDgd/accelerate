#pragma once
#include <accelerate/execution/context.hpp>
#include <accelerate/execution/program/binary.hpp>
#include <accelerate/execution/program/source.hpp>

namespace accelerate::execution {
	class build_target
	{
		friend class builder;
		friend class program;
	public:
		using native_handle_type = ::cl_program;

	public:
		template <typename InputIterator>
		static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, source>, build_target>
			from_source(context&, InputIterator&&, InputIterator&&);

		template <typename InputIterator>
		static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, binary>, build_target>
			from_binary(context&, InputIterator&&, InputIterator&&);

		template <typename SourceType>
		static std::enable_if_t<std::is_same_v<std::remove_reference_t<SourceType>, source>, build_target>
			from_source(context&, SourceType&&);

		template <typename BinaryType>
		static std::enable_if_t<std::is_same_v<std::remove_reference_t<BinaryType>, binary>, build_target>
			from_source(context&, BinaryType&&);

	private:
		build_target(native_handle_type, std::size_t*, device::device**, std::size_t);

	public:
		~build_target();
		build_target (build_target&);
		build_target (build_target&&);

	private:
		native_handle_type __M_program_handle	   ;
		std::size_t*	   __M_program_size		   ;
		
		device::device**   __M_program_target	   ;
		std::size_t		   __M_program_target_count;
	};
}

template <typename InputIterator>
static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, accelerate::execution::source>, accelerate::execution::build_target>
accelerate::execution::build_target::from_source(context& ctx, InputIterator&& begin, InputIterator&& end)
{
	auto		 src_count  = std::distance(begin, end);
	
	char**		 src_ptr    = new char*			 [src_count];
	std::size_t* src_size   = new std::size_t	 [src_count];
	
	auto**	     src_target = new device::device*[src_count];

	for (auto src_idx = 0; begin != end; ++src_idx, ++begin)
	{
		src_ptr   [src_idx] = reinterpret_cast<char*>((*begin).__M_src_ptr)  ;
		src_size  [src_idx] =					      (*begin).__M_src_size  ;
		src_target[src_idx] =						 &(*begin).__M_src_device;
	}

	auto src_program =::clCreateProgramWithSource(ctx.native_handle(), src_count, 
												 (const char**)		   src_ptr  , 
												 (const std::size_t*)  src_size , nullptr);

	return  build_target(src_program, src_size, src_target, src_count);
}

template <typename InputIterator>
static std::enable_if_t<std::is_same_v<typename InputIterator::value_type, accelerate::execution::binary>, accelerate::execution::build_target>
accelerate::execution::build_target::from_binary(context& ctx, InputIterator&& begin, InputIterator&& end)
{
	auto		 src_count  = std::distance(begin, end);
	
	char**		 src_ptr    = new char*			 [src_count];
	std::size_t* src_size   = new std::size_t    [src_count];
	
	auto**		 src_target = new device::device*[src_count];

	for (auto src_idx = 0; begin != end; ++src_idx, ++begin)
	{
		src_ptr   [src_idx] = reinterpret_cast<char*>((*begin).__M_binary_pointer);
		src_size  [src_idx] =					      (*begin).__M_binary_size	  ;
		src_target[src_idx] =						 &(*begin).__M_binary_target  ;
	}

	auto src_program =::clCreateProgramWithBinary(ctx.native_handle(),  src_count ,
												 (const ::cl_device_id*)src_target,
												 (const std::size_t*)   src_size  ,
												 (const std::uint8_t**) src_ptr   ,
												  nullptr, nullptr);

	return build_target(src_program, src_size, src_target, src_count);
}

template <typename SourceType>
std::enable_if_t<std::is_same_v<std::remove_reference_t<SourceType>, accelerate::execution::source>, accelerate::execution::build_target>
accelerate::execution::build_target::from_source(context& ctx, SourceType&& src)
{
	char**			 src_ptr    =  new char*;
					*src_ptr    =  (char*)src.__M_src_pointer;

	std::size_t*	 src_size	=  new std::size_t;
					*src_size   =  src.__M_src_size;
	device::device** src_target =  new device::device*;
					*src_target = &src.__M_src_device;

	auto		     src_program = ::clCreateProgramWithSource(ctx.native_handle(), 1	  ,
															  (const char**)	  src_ptr ,
															  (const std::size_t*)src_size,
															   nullptr);

	return build_target(src_program, src_size, src_target, 1);
}

template <typename BinaryType>
std::enable_if_t<std::is_same_v<std::remove_reference_t<BinaryType>, accelerate::execution::binary>, accelerate::execution::build_target>
accelerate::execution::build_target::from_source(context& ctx, BinaryType&& bin)
{
	char**			 src_ptr    =  new char*;
					*src_ptr    =  (char*)bin.__M_binary_pointer;

	std::size_t*	 src_size	=  new std::size_t;
				    *src_size   =  bin.__M_binary_size;

	device::device** src_target =  new device::device*  ;
					*src_target = &bin.__M_binary_device;

	auto		     src_program = ::clCreateProgramWithBinary(ctx.native_handle(),			  1,
															  (const ::cl_device_id*)src_target,
															  (const std::size_t*)   src_size  ,
															  (const unsigned char**)src_ptr   ,
															   nullptr, nullptr);
}