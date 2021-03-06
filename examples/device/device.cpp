#include <accelerate/device/platform.hpp>
#include <accelerate/device/platform_enumerator.hpp>

#include <accelerate/device/device.hpp>
#include <accelerate/device/device_enumerator.hpp>

#include <iostream>

int main()
{
	accelerate::platform::enumerator pf_enum;
	for (auto&& pf : pf_enum)
		std::cout << pf[accelerate::platform::version] << std::endl;

	auto							 pf_iterator =  pf_enum.begin();
	auto							 pf			 = *pf_iterator;

	accelerate::device::enumerator   dv_enum(accelerate::device::all, pf);
	for (auto&& dv : dv_enum)
		std::cout << dv[accelerate::device::name] << std::endl;
}