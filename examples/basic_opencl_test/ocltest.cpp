#include <iostream>
#include <memory/io_map/io_map.hpp>

#include <accelerate/device/platform_enumerator.hpp>
#include <accelerate/device/platform.hpp>

#include <accelerate/device/device_enumerator.hpp>
#include <accelerate/device/device.hpp>

#include <accelerate/execution/program/build_target.hpp>
#include <accelerate/execution/program/program.hpp>
#include <accelerate/execution/executor.hpp>

#include <accelerate/builder/builder.hpp>
#include <accelerate/execution/kernel.hpp>

#include <accelerate/task/kernel/kernel_task.hpp>

int main()
{
	accelerate::platform::enumerator accel_if_enumerator;
	auto							 accel_if = *accel_if_enumerator.begin();
	
	accelerate::device::enumerator accel_dev_enumerator(accelerate::device::gpu, accel_if);
	auto						   accel_dev = *accel_dev_enumerator.begin();
	memory::io_map				   accel_src("C:\\Users\\MinusOne\\Projects\\accelerate\\examples\\basic_opencl_test\\test.cl");

	auto								accel_ctx		   = accelerate::execution::context::from_device({ accel_dev });	
	accelerate::execution::builder		accel_builder;
	auto								accel_source	   = accelerate::execution::source::from_memory(accel_dev, accel_src);
	accelerate::execution::build_target accel_build_target = accelerate::execution::build_target::from_source(accel_ctx, accel_source);
	auto								accel_program = accel_builder(accel_build_target);

	int a[16] = { 1, }, b[16] = { 2, }, c[16] = { 0, };
	//accelerate::execution::kernel <void(int*, int*, int*)> accel_kernel(accel_program, "CLSimpleKernel");
	//accelerate::task::kernel::task<void(int*, int*, int*)> accel_task  (accel_ctx, accel_kernel, a, b, c);
	auto test_args = accelerate::task::kernel::make_argument(accel_ctx, a, b, c);
}