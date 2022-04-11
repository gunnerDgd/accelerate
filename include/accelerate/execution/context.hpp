#pragma once
#include <accelerate/device/device.hpp>
#include <initializer_list>

namespace accelerate::execution {
	class context
	{
	public:
		using native_handle_type = cl_context;
		using refcount_type      = cl_uint;

		~context();
		context (const context&)  noexcept;
		context (const context&&) noexcept;
		
		template <typename DeviceType>
		static std::enable_if_t<std::is_base_of_v<device::query::device_id, DeviceType>, context> 
					   from_device_type(DeviceType);
		static context from_device	   (std::initializer_list<device::device>);

	public:
		native_handle_type native_handle() { return __M_ctx_handle; }
	
	private:
		context(native_handle_type);
		native_handle_type __M_ctx_handle;
	};
}

template <typename DeviceType>
std::enable_if_t<std::is_base_of_v<accelerate::device::query::device_id, DeviceType>, 
								   accelerate::execution::context>  accelerate::execution::context::from_device_type(DeviceType)
{
	auto		   dv_context = ::clCreateContextFromType(nullptr, DeviceType::id, nullptr, nullptr, nullptr);
	return context(dv_context);
}
