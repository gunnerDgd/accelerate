#include <accelerate/execution/context.hpp>

accelerate::execution::context accelerate::execution::context::from_device(std::initializer_list<device::device> dv_list)
{
	auto      dv_hnd	  = new device::device::native_handle_type[dv_list.size()];
	auto	  dv_list_ptr = (device::device*)dv_list.begin();

	for (int dv_idx = 0; dv_idx < dv_list.size(); dv_idx++)
		dv_hnd[dv_idx] = dv_list_ptr[dv_idx].native_handle();

	auto      dv_context = ::clCreateContext(nullptr, dv_list.size(), (const cl_device_id*)dv_list_ptr, nullptr, nullptr, nullptr);
	delete[]  dv_hnd;

	return context(dv_context);
}

accelerate::execution::context::context (native_handle_type hnd) : __M_ctx_handle(hnd) {  }
accelerate::execution::context::~context()											   { ::clReleaseContext(__M_ctx_handle); }

accelerate::execution::context::context (const context&& move) noexcept : __M_ctx_handle(move.__M_ctx_handle) {  }
accelerate::execution::context::context (const context& copy)  noexcept : __M_ctx_handle(copy.__M_ctx_handle) { ::clRetainContext (__M_ctx_handle); }
