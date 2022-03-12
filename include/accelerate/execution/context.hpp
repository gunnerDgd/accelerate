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
		context (context&);
		context (context&&) noexcept;
		
		template <typename DeviceType>
		static std::enable_if_t<std::is_base_of_v<device::query::device_type, DeviceType>, context> 
					   from_device_type(DeviceType);
		static context from_device	   (std::initializer_list<device::device>);
	
	private:
		context(native_handle_type);
	private:
		native_handle_type __M_ctx_handle;
	};
}