#pragma once
#include <accelerate/memory/memory.hpp>

namespace accelerate::memory {
	template <typename MemoryType, device_memory::size_type MemoryCount> 
	class device_memory::unmapped
	{
	public:
		using					value_type					  = MemoryType ;
		using					pointer						  = MemoryType*;
		using					reference					  = MemoryType&;
		static inline constexpr device_memory::size_type size = MemoryCount * sizeof(MemoryType);

		template <typename AccessType>
		unmapped (executor_type&, AccessType);
		~unmapped();

		unmapped (const unmapped&) ;
		unmapped (const unmapped&&);

	public:
		device_memory& get_memory() { return __M_unmapped_handle; }

	private:
		device_memory __M_unmapped_handle;
	};
}

template <typename MemoryType, accelerate::memory::types::size_type MemoryCount>
template <typename AccessType>
accelerate::memory::device_memory::unmapped<MemoryType, MemoryCount>::unmapped(executor_type& exec, AccessType) 
	: __M_unmapped_handle(exec, ::clCreateBuffer(exec.get_context(),
												 AccessType::value ,
												 sizeof(MemoryType),
												 nullptr		   ,
												 nullptr))		   {  }

template <typename MemoryType, accelerate::memory::types::size_type MemoryCount>
accelerate::memory::device_memory::unmapped<MemoryType, MemoryCount>::~unmapped() {  }

template <typename MemoryType, accelerate::memory::types::size_type MemoryCount>
accelerate::memory::device_memory::unmapped<MemoryType, MemoryCount>::unmapped (const unmapped& copy)
	: __M_unmapped_handle (copy.__M_unmapped_handle)							  {  }

template <typename MemoryType, accelerate::memory::types::size_type MemoryCount>
accelerate::memory::device_memory::unmapped<MemoryType, MemoryCount>::unmapped(const unmapped&& move)
	: __M_unmapped_handle (std::move(move.__M_unmapped_handle)) {  }