#include <accelerate/device/device_enumerator.hpp>

accelerate::device::enumerator::~enumerator()
{
	delete[] __M_dvenum_handle;
}

accelerate::device::device::device(native_handle_type hnd) : __M_dev_handle(hnd)
{

}

accelerate::device::enumerator::iterator::iterator(enumerator& hnd) : __M_it_enum (hnd),
																	  __M_it_count(0)
{

}

accelerate::device::enumerator::iterator::value_type accelerate::device::enumerator::iterator::operator* ()
{
	return device(__M_it_enum.__M_dvenum_handle[__M_it_count]);
}

accelerate::device::enumerator::iterator& accelerate::device::enumerator::iterator::operator++()
{
	if (__M_it_count < __M_it_enum.__M_dvenum_count)
		__M_it_count++;

	return *this;
}

bool accelerate::device::enumerator::iterator::operator==(iterator& cmp)
{
	return __M_it_count == cmp.__M_it_count;
}

bool accelerate::device::enumerator::iterator::operator!=(iterator& cmp)
{
	return __M_it_count != cmp.__M_it_count;
}

accelerate::device::enumerator::count_type accelerate::device::enumerator::size()
{
	return __M_dvenum_count;
}

accelerate::device::enumerator::iterator accelerate::device::enumerator::begin()
{
	return iterator(*this);
}

accelerate::device::enumerator::iterator accelerate::device::enumerator::end()
{
	iterator dv_return(*this);
			 dv_return.__M_it_count = __M_dvenum_count;

	return	 dv_return;
}