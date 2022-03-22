#pragma once
#include <accelerate/execution/executor.hpp>
#include <accelerate/memory/memory_traits.hpp>

namespace accelerate::memory {
	class mapped
	{
	public:
		using pointer_type	  = std::uint8_t* ;
		using size_type		  = std::size_t   ;
		using difference_type = std::ptrdiff_t;
		
		using			 native_context_type = execution::context::native_handle_type;
		using			 native_handle_type  = ::cl_mem;
		static constexpr native_handle_type invalid_handle = nullptr;

	public:
		template <typename MemoryObject, typename AccessType>
		mapped (execution::executor&, AccessType, MemoryObject&&);
		~mapped();

		mapped (mapped&);
		mapped (mapped&&);

	public:
		execution::executor& get_executor () { return __M_mapped_executor; }
		native_handle_type   native_handle() { return __M_mapped_handle  ; }
		size_type			 size		  () { return __M_mapped_size    ; }

	private:
		native_handle_type   __M_mapped_handle ;
		pointer_type	     __M_mapped_pointer;
		size_type		     __M_mapped_size   ;

		execution::executor& __M_mapped_executor;
		execution::context & __M_mapped_context ;
	};
}

template <typename MemoryObject, typename AccessType>
accelerate::memory::mapped::mapped(execution::executor& exec, AccessType, MemoryObject&& memobj)
	: __M_mapped_size    (memobj.size()),
	  __M_mapped_pointer (memobj.address()),
	  __M_mapped_executor(exec),
	  __M_mapped_context (exec.get_context())
{
	__M_mapped_handle = ::clCreateBuffer(exec.get_context().native_handle(),
										 AccessType::value ,
										 __M_mapped_size   ,
										 __M_mapped_pointer,
										 nullptr);

					    ::clRetainMemObject(__M_mapped_handle);
}