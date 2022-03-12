#pragma once
#include <CL/cl.h>
#include <accelerate/device/device.hpp>
#include <accelerate/device/platform.hpp>

namespace accelerate::device {
	class enumerator
	{
	public:
		using native_handle_type = cl_device_id;
		using count_type		 = int;
		class iterator;

		template <typename DeviceType>
		enumerator (DeviceType, platform::platform&);
		~enumerator();

	public:
		count_type size ();
		iterator   begin();
		iterator   end  ();
		
	private:
		native_handle_type* __M_dvenum_handle;
		count_type			__M_dvenum_count ;
	};

	class enumerator::iterator
	{
		friend class enumerator;
		iterator	(enumerator&);
	public:
		using value_type	  = device;
		using pointer		  = device*;
		using reference		  = device&;
		using iterator_tag    = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		
	public:
		value_type			  operator* ();
		enumerator::iterator& operator++();

		bool				  operator==(iterator&);
		bool				  operator!=(iterator&);

	private:
		count_type  __M_it_count;
		enumerator& __M_it_enum ;
	};
}

template <typename DeviceType>
accelerate::device::enumerator::enumerator(DeviceType, platform::platform& pl)
	: __M_dvenum_handle(new native_handle_type[256])
{
	::clGetDeviceIDs(pl.__M_pf_handle, DeviceType::id, 256, __M_dvenum_handle, (cl_uint*)&__M_dvenum_count);
}