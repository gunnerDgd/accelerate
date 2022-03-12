#pragma once
#include <CL/cl.h>
#include <string>

namespace accelerate::device::query {
	struct device_type {};
	struct query_type  {};

	struct cpu				  : public device_type { static constexpr int id = CL_DEVICE_TYPE_CPU; };
	struct gpu				  : public device_type { static constexpr int id = CL_DEVICE_TYPE_GPU; };
	struct all				  : public device_type { static constexpr int id = CL_DEVICE_TYPE_ALL; };

	struct address_size		  : public query_type  { typedef std::uint32_t  type; static constexpr int id = CL_DEVICE_ADDRESS_BITS; };
	struct compiler_available : public query_type  { typedef bool		    type; static constexpr int id = CL_DEVICE_COMPILER_AVAILABLE; };
	struct device_type		  : public query_type  { typedef cl_device_type type; static constexpr int id = CL_DEVICE_TYPE; };
	struct vendor			  : public query_type  { typedef std::string    type; static constexpr int id = CL_DEVICE_VENDOR; };
	struct name				  : public query_type  { typedef std::string    type; static constexpr int id = CL_DEVICE_NAME; };
}

namespace accelerate::device {
	inline constexpr query::cpu cpu;
	inline constexpr query::gpu gpu;
	inline constexpr query::all all;

	inline constexpr query::address_size	   address_size;
	inline constexpr query::compiler_available compiler_available;
	inline constexpr query::device_type		   device_type;
	inline constexpr query::vendor			   vendor ;
	inline constexpr query::name			   name;
}