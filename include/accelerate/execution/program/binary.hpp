#pragma once
#include <accelerate/device/device.hpp>

namespace accelerate::execution {
	class binary
	{
		friend class program;
		friend class builder;

		using		 binary_pointer = std::uint8_t*  ;
		using		 binary_size    = std::size_t    ;
		using		 binary_target  = device::device&;
		
		binary(device::device&, binary_pointer, binary_size);
	public:
		template <typename MemoryObject>
		static binary from_memory (device::device&, MemoryObject&&);

	private:
		binary_target& __M_binary_device ;
		binary_pointer __M_binary_pointer;
		binary_size    __M_binary_size	 ;
	};
}

template <typename MemoryObject>
accelerate::execution::binary 
accelerate::execution::binary::from_memory(device::device& src_dev, MemoryObject&& src_mem)
{
	return binary(src_dev, src_mem.address(), src_mem.size());
}

accelerate::execution::binary::binary(device::device& src_dev, binary_pointer src_pointer, binary_size src_size)
	: __M_binary_device (src_dev)	 ,
	  __M_binary_pointer(src_pointer),
	  __M_binary_size	(src_size)	 {  }