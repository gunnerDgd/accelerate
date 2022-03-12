#pragma once
#include <accelerate/device/declare.hpp>
#include <accelerate/device/platform_traits.hpp>

#include <string>

namespace accelerate::platform {
	class platform
	{
		friend class enumerator;
		friend class accelerate::device::enumerator;
	public:
		using native_handle_type = cl_platform_id;
	private:
		platform(native_handle_type);
		platform(platform&)  = default;
		platform(platform&&) = default;

	public:
		template <typename QueryType>
		auto operator[](QueryType);

	private:
		native_handle_type __M_pf_handle;
	};
}

template <typename QueryType>
auto accelerate::platform::platform::operator[](QueryType)
{
	std::size_t				 pf_query_retlen;
	char				     pf_query_retchar[256];

	::clGetPlatformInfo   (__M_pf_handle, QueryType::id, 256, (void*)pf_query_retchar, &pf_query_retlen);
	return typename QueryType::type(pf_query_retchar, pf_query_retlen);
}

