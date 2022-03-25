#pragma once
#include <accelerate/execution/context.hpp>
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
		mapped (execution::context&, AccessType, MemoryObject&&);
		template <typename AccessType, typename MemoryType>
		mapped (execution::context&, AccessType, MemoryType*, size_type);
		template <typename AccessType, typename MemoryType, std::size_t MemoryCount>
		mapped (execution::context&, AccessType, MemoryType(&)[MemoryCount]);
		~mapped();

		mapped (mapped&);
		mapped (mapped&&);

	public:
		native_handle_type   native_handle() { return __M_mapped_handle  ; }
		size_type			 size		  () { return __M_mapped_size    ; }

	private:
		native_handle_type   __M_mapped_handle ;
		pointer_type	     __M_mapped_pointer;
		size_type		     __M_mapped_size   ;
		execution::context & __M_mapped_context ;
	};
}

template <typename AccessType, typename MemoryType, std::size_t MemoryCount>
accelerate::memory::mapped::mapped(execution::context& exec, AccessType, MemoryType(&memobj)[MemoryCount])
	: __M_mapped_size	(sizeof(MemoryType) * MemoryCount),
	  __M_mapped_pointer((pointer_type)memobj),
	  __M_mapped_context(exec)
{
	__M_mapped_handle = ::clCreateBuffer(exec.native_handle(),
										 AccessType::value ,
										 __M_mapped_size   ,
										 __M_mapped_pointer,
										 nullptr);

					    ::clRetainMemObject(__M_mapped_handle);
}

template <typename AccessType, typename MemoryType>
accelerate::memory::mapped::mapped(execution::context& exec, AccessType, MemoryType* memobj, size_type memsize)
	: __M_mapped_size				   (memsize),
	  __M_mapped_pointer ((pointer_type)memobj) ,
	  __M_mapped_context			   (exec)
{
	__M_mapped_handle = ::clCreateBuffer(exec.native_handle(),
										 AccessType::value ,
										 __M_mapped_size   ,
										 __M_mapped_pointer,
										 nullptr);

					    ::clRetainMemObject(__M_mapped_handle);
}

template <typename MemoryObject, typename AccessType>
accelerate::memory::mapped::mapped(execution::context& exec, AccessType, MemoryObject&& memobj)
	: __M_mapped_size    (memobj.size()),
	  __M_mapped_pointer (memobj.address()),
	  __M_mapped_context (exec.native_handle())
{
	__M_mapped_handle = ::clCreateBuffer(exec.native_handle(),
										 AccessType::value ,
										 __M_mapped_size   ,
										 __M_mapped_pointer,
										 nullptr);

					    ::clRetainMemObject(__M_mapped_handle);
}