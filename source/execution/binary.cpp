#include <accelerate/execution/program/binary.hpp>

accelerate::execution::binary::binary(device::device& src_dev, binary_pointer src_pointer, binary_size src_size)
	: __M_binary_device (src_dev)	 ,
	  __M_binary_pointer(src_pointer),
	  __M_binary_size	(src_size)	 {  }