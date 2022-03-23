#pragma once
#include <accelerate/device/device.hpp>
#include <string>

namespace accelerate::execution {
	class source
	{
		friend class program;
		friend class builder;

		enum class source_location { memory_object, heap };
		using	   source_pointer = std::uint8_t* ;
		using	   source_size    = std::size_t   ;
		using      source_target  = device::device;

		source (device::device&, source_location, source_pointer, source_size);
		~source();
	public:
		using native_device_handle = device::device::native_handle_type;
		using string_type		   = std::string;
	public:
		template <typename MemoryObject>
		static source   from_memory  (device::device&, MemoryObject&&);
		static source   from_string  (device::device&, std::string)   ;

	private:
		source_location __M_src_location;
		source_target&  __M_src_device  ;

		source_pointer	__M_src_pointer ;
		source_size		__M_src_size	;
	};
}

template <typename MemoryObject>
accelerate::execution::source 
accelerate::execution::source::from_memory(device::device& dev, MemoryObject&& memobj)
{
	return source(dev, source_location::memory_object, memobj.address(), memobj.size());
}