#pragma once
#include <accelerate/device/platform.hpp>
#include <iterator>

namespace accelerate::platform {
	class enumerator
	{
	public:
		using native_handle_type = cl_platform_id;
		using count_type		 = cl_uint;
		class iterator;

	public:
		enumerator ();
		~enumerator() { delete[] __M_pf_handle; }

	public:
		count_type size ();
		iterator   begin();
		iterator   end  ();
		
	private:
		native_handle_type* __M_pf_handle;
		count_type			__M_pf_count ;
	};

	class enumerator::iterator
	{
		friend class enumerator;
		iterator(enumerator&);
	public:
		using value_type      = platform;
		using reference       = platform&;
		using pointer         = platform*;
		using iterator_tag    = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;

	public:
		value_type			  operator* ();
		enumerator::iterator& operator++();

	public:
		bool operator== (iterator&);
		bool operator!= (iterator&);

	private:
		enumerator&			   __M_it_enumerator;
		enumerator::count_type __M_it_index;
	};
}

