#pragma once
#include <accelerate/execution/context.hpp>
#include <accelerate/memory/memory_traits.hpp>

namespace accelerate::memory {
	class unmapped
	{
	public:
		using size_type		  = std::size_t;
		using difference_type = std::ptrdiff_t;
		
		using			 native_context_type = execution::context::native_handle_type;
		using			 native_handle_type  = ::cl_mem;
		static constexpr native_handle_type invalid_handle = nullptr;

		template <typename AccessType>
		unmapped (execution::context&, AccessType, size_type);
		~unmapped();

		unmapped (unmapped&);
		unmapped (unmapped&&);

	public:
		native_handle_type native_handle();
		size_type		   size			();

	private:
		native_handle_type  __M_unmapped_handle ;
		size_type		    __M_unmapped_size   ;
		execution::context& __M_unmapped_context;
	};
}

template <typename AccessType>
accelerate::memory::unmapped::unmapped(execution::context& exec, AccessType, size_type size)
	: __M_unmapped_context(exec),
	  __M_unmapped_size   (size)
{
	__M_unmapped_handle = ::clCreateBuffer(exec.native_handle(),
										   AccessType::value,
										   size,
										   nullptr, nullptr);
						  ::clRetainMemObject(__M_unmapped_handle);
}