#pragma once
#include <CL/cl.hpp>

#include <accelerate/device/declare.hpp>
#include <accelerate/device/device_traits.hpp>

namespace accelerate::device {
	class device
	{
	public:
		using native_handle_type = cl_device_id;
	private:
		friend class enumerator;
		device(native_handle_type);
	
	public:
		template <typename QueryType>
		std::enable_if_t<std::is_same_v<std::string, typename QueryType::type>, typename QueryType::type>
			operator[](QueryType);
		template <typename QueryType>
		std::enable_if_t<!std::is_same_v<std::string, typename QueryType::type>, typename QueryType::type>
			operator[](QueryType);

	public:
		native_handle_type native_handle() { return __M_dev_handle; }

	public:
		native_handle_type __M_dev_handle;
	};
}

template <typename QueryType>
std::enable_if_t<std::is_same_v<std::string, typename QueryType::type>, typename QueryType::type>
accelerate::device::device::operator[](QueryType)
{
	char		dv_query_res[256];
	std::size_t dv_query_size;

	::clGetDeviceInfo (__M_dev_handle, QueryType::id, 256, (void*)dv_query_res, &dv_query_size);
	return std::string(dv_query_res, dv_query_size);
}

template <typename QueryType>
std::enable_if_t<!std::is_same_v<std::string, typename QueryType::type>, typename QueryType::type>
accelerate::device::device::operator[](QueryType)
{
	typename QueryType::type dv_query_res ;
	std::size_t			     dv_query_size;

	::clGetDeviceInfo(__M_dev_handle, QueryType::id, sizeof(typename QueryType::type), (void*)&dv_query_res, &dv_query_size);
	return dv_query_res;
}