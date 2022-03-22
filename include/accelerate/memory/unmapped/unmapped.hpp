#pragma once
#include <accelerate/execution/executor.hpp>
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
		unmapped (execution::executor&, AccessType, size_type) 
			requires std::is_base_of_v<access_type::access_mode, AccessType>;
		~unmapped();

		unmapped (unmapped&);
		unmapped (unmapped&&);

	public:
		native_handle_type native_handle();
		size_type		   size			();

	private:
		native_handle_type   __M_unmapped_handle  ;
		size_type		     __M_unmapped_size    ;
		execution::executor& __M_unmapped_executor;
	};
}

template <typename AccessType>
accelerate::memory::unmapped::unmapped(execution::executor& exec, AccessType, size_type size)
	requires std::is_base_of_v<accelerate::memory::access_type::access_mode, AccessType>
	: __M_unmapped_executor(exec),
	  __M_unmapped_size    (size)
{
	__M_unmapped_handle = ::clCreateBuffer(exec.get_context().native_handle(),
										   AccessType::value,
										   size,
										   nullptr, nullptr);
						  ::clRetainMemObject(__M_unmapped_handle);
}