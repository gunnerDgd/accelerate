#include <accelerate/device/platform_enumerator.hpp>
#include <accelerate/device/platform.hpp>

accelerate::platform::enumerator::enumerator() : __M_pf_handle(new native_handle_type[256])
{
	::clGetPlatformIDs(256, __M_pf_handle, &__M_pf_count);
}

accelerate::platform::enumerator::iterator::iterator(enumerator& pf_enum) : __M_it_enumerator(pf_enum), 
																			__M_it_index	 (0)
{

}

accelerate::platform::enumerator::count_type accelerate::platform::enumerator::size()
{
	return __M_pf_count;
}

accelerate::platform::enumerator::iterator   accelerate::platform::enumerator::begin()
{
	return iterator(*this);
}

accelerate::platform::enumerator::iterator   accelerate::platform::enumerator::end()
{
	iterator end_iterator(*this);
			 end_iterator.__M_it_index = __M_pf_count;

	return   end_iterator;
}

accelerate::platform::platform::platform(native_handle_type hnd) : __M_pf_handle(hnd)
{

}

accelerate::platform::enumerator::iterator::value_type accelerate::platform::enumerator::iterator::operator* ()
{
	return value_type(__M_it_enumerator.__M_pf_handle[__M_it_index]);
}

accelerate::platform::enumerator::iterator& accelerate::platform::enumerator::iterator::operator++()
{
	if (__M_it_index < __M_it_enumerator.__M_pf_count)
		__M_it_index++;
	
	return *this;
}

bool accelerate::platform::enumerator::iterator::operator== (iterator& cmp)
{
	return cmp.__M_it_index == __M_it_index;
}

bool accelerate::platform::enumerator::iterator::operator!= (iterator& cmp)
{
	return cmp.__M_it_index != __M_it_index;
}