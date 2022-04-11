#pragma once
#include <type_traits>
#include <CL/cl.h>

namespace accelerate::memory::access::types {
	struct access_mode {};

	struct read_only  : public access_mode { static constexpr ::cl_mem_flags value = CL_MEM_READ_ONLY ; };
	struct write_only : public access_mode { static constexpr ::cl_mem_flags value = CL_MEM_WRITE_ONLY; };
	struct all		  : public access_mode { static constexpr ::cl_mem_flags value = CL_MEM_READ_WRITE; };
}

namespace accelerate::memory::types {
	using size_type		  = ::cl_uint;
	using difference_type = ::cl_int ;
}

namespace accelerate::memory {
	inline constexpr access::types::read_only  read_only ;
	inline constexpr access::types::write_only write_only;
	inline constexpr access::types::all	       all		 ;
}