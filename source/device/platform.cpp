#include <accelerate/device/platform_enumerator.hpp>
#include <accelerate/device/platform.hpp>

accelerate::platform::enumerator::enumerator()
{
	::clGetPlatformIDs(-1, __M_pf_handle, &__M_pf_count);
}

typename accelerate::platform::enumerator::iterator::value_type 
		 accelerate::platform::enumerator::iterator::operator* ()
{
	return value_type(__M_it_enumerator.__M_pf_handle[__M_it_index]);
}

typename accelerate::platform::enumerator::iterator& 
		 accelerate::platform::enumerator::iterator::operator++()
{
	if (__M_it_index < __M_it_enumerator.__M_pf_count)
		__M_it_index++;
	
	return *this;
}