#include <accelerate/builder/source.hpp>

accelerate::build::source::source(device::device& src_device, source_location src_location, source_pointer src_ptr, source_size src_len)
	: __M_src_device  (src_device) ,
	  __M_src_pointer (src_ptr)    ,
	  __M_src_size    (src_len)    ,
	  __M_src_location(src_location) {  }

accelerate::build::source::~source()
{
	if (__M_src_location == source_location::heap)
		delete[] __M_src_pointer;
}

accelerate::build::source
accelerate::build::source::from_string(device::device& src_device, std::string src_string)
{
	std::size_t src_size   = src_string.size();
	char*		src_memory = new char[src_size];

	std::memcpy  (src_memory, src_string.c_str(), src_size);
	return source(src_device, source_location::heap, (std::uint8_t*)src_memory, src_size);
}