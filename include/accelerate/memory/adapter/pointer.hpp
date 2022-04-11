#pragma once
#include <type_traits>
#include <accelerate/memory/memory.hpp>

namespace accelerate::memory::adapter {
	template <typename AccessType> class pointer
	{
	public:
		using value_type	  = AccessType;
		using size_type		  = typename device_memory::size_type;
		using difference_type = typename device_memory::difference_type;

		using executor_type   = execution::executor::native_handle_type;
		using memory_handle   = device_memory	   ::native_handle_type;

	public:
		template <typename MemoryObject>
		pointer (MemoryObject&&);
		~pointer()				{  }

	public:
		template <typename InputParameter>
		pointer&   operator= (InputParameter&&);
		value_type operator* ()				   ;
		
		pointer&   operator+ (difference_type) ;
		pointer&   operator++()				   ;
		pointer    operator++(int)			   ;

		pointer&   operator- (difference_type) ;
		pointer&   operator--()				   ;
		pointer    operator--(int)			   ;

	private:
		executor_type   __M_pointer_io_exec   ;
		memory_handle   __M_pointer_memhnd    ;
		difference_type __M_pointer_memoff = 0;
	};
}

template <typename AccessType>
template <typename MemoryObject>
accelerate::memory::adapter::pointer<AccessType>::pointer(MemoryObject&& memobj)
	: __M_pointer_io_exec(memobj.get_memory().get_executor()),
	  __M_pointer_memhnd (memobj.get_memory())				 {  }

template <typename AccessType>
template <typename InputParameter>
accelerate::memory::adapter::pointer<AccessType>& accelerate::memory::adapter::pointer<AccessType>::operator= (InputParameter&& wrbuf)
{
	::clEnqueueWriteBuffer(__M_pointer_io_exec, 
						   __M_pointer_memhnd ,
						   __M_pointer_memoff ,
						   sizeof(value_type) , &wrbuf, 0, nullptr, nullptr);
}

template <typename AccessType>
accelerate::memory::adapter::pointer<AccessType>::value_type accelerate::memory::adapter::pointer<AccessType>::operator* ()
{
	value_type rdbuf;
	::clEnqueueReadBuffer(__M_pointer_io_exec, 
						  __M_pointer_memhnd ,
						  __M_pointer_memoff ,
						  sizeof(value_type) , &rdbuf, 0, nullptr, nullptr);

	return rdbuf;
}

template <typename AccessType>
accelerate::memory::adapter::pointer<AccessType>& accelerate::memory::adapter::pointer<AccessType>::operator+ (difference_type diff)
{
	__M_pointer_memoff += diff * sizeof(value_type);
	return *this;
}

template <typename AccessType>
accelerate::memory::adapter::pointer<AccessType>& accelerate::memory::adapter::pointer<AccessType>::operator++()
{
	__M_pointer_memoff += sizeof(value_type);
	return *this;
}

template <typename AccessType>
accelerate::memory::adapter::pointer<AccessType> accelerate::memory::adapter::pointer<AccessType>::operator++(int)
{
	__M_pointer_memoff += sizeof(value_type);
	return *this;
}

template <typename AccessType>
accelerate::memory::adapter::pointer<AccessType>& accelerate::memory::adapter::pointer<AccessType>::operator- (difference_type diff)
{
	__M_pointer_memoff -= diff * sizeof(value_type);
	return *this;
}

template <typename AccessType>
accelerate::memory::adapter::pointer<AccessType>& accelerate::memory::adapter::pointer<AccessType>::operator--()
{
	__M_pointer_memoff -= sizeof(value_type);
	return *this;
}

template <typename AccessType>
accelerate::memory::adapter::pointer<AccessType> accelerate::memory::adapter::pointer<AccessType>::operator--(int)
{
	__M_pointer_memoff -= sizeof(value_type);
	return *this;
}