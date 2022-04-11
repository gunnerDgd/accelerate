#pragma once
#include <accelerate/memory/memory.hpp>

namespace accelerate::memory {
	template <typename MemoryType, device_memory::size_type MemoryCount> 
	class device_memory::mapped
	{
	public:
		using								   value_type     = MemoryType ;
		using								   pointer		  = MemoryType*;
		using								   reference      = MemoryType&;
		static inline constexpr device_memory::size_type size = MemoryCount * sizeof(MemoryType);

	public:
		template <typename MemoryObject, typename AccessType>
		mapped (executor_type&, AccessType, MemoryObject&&);
		~mapped();

		mapped (const mapped&);
		mapped (const mapped&&);

	public:
		device_memory& get_memory() { return __M_mapped_handle; }

	private:
		device_memory __M_mapped_handle;
	};
}

template <typename MemoryType, accelerate::memory::device_memory::size_type MemoryCount>
template <typename MemoryObject, typename AccessType>
accelerate::memory::device_memory::mapped<MemoryType, MemoryCount>::mapped(executor_type& exec, AccessType, MemoryObject&& memobj)
	: __M_mapped_handle(exec, ::clCreateBuffer(exec.native_handle(),
											   AccessType::value   ,
											   memobj.size()	   ,
											   memobj.pointer()    ,
											   nullptr))		   {  }

template <typename MemoryType, accelerate::memory::device_memory::size_type MemoryCount>
accelerate::memory::device_memory::mapped<MemoryType, MemoryCount>::~mapped() {  }

template <typename MemoryType, accelerate::memory::types::size_type MemoryCount>
accelerate::memory::device_memory::mapped<MemoryType, MemoryCount>::mapped(const mapped& copy)
	: __M_mapped_handle(copy.__M_mapped_handle)								  {  }

template <typename MemoryType, accelerate::memory::types::size_type MemoryCount>
accelerate::memory::device_memory::mapped<MemoryType, MemoryCount>::mapped(const mapped&& move)
	: __M_mapped_handle(std::move(move)) {  }