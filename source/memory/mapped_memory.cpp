#include <accelerate/memory/mapped/mapped.hpp>

accelerate::memory::mapped::~mapped() { ::clReleaseMemObject(__M_mapped_handle); }

accelerate::memory::mapped::mapped(mapped& copy) : __M_mapped_handle (copy.__M_mapped_handle) ,
												   __M_mapped_pointer(copy.__M_mapped_pointer),
												   __M_mapped_size   (copy.__M_mapped_size)   ,
												   __M_mapped_context(copy.__M_mapped_context)
{
	::clRetainMemObject(__M_mapped_handle);
}

accelerate::memory::mapped::mapped(mapped&& move): __M_mapped_handle (move.__M_mapped_handle) ,
												   __M_mapped_pointer(move.__M_mapped_pointer),
												   __M_mapped_size   (move.__M_mapped_size)   ,
												   __M_mapped_context(move.__M_mapped_context)
{
	__M_mapped_handle  = invalid_handle;
	__M_mapped_pointer = nullptr;
	__M_mapped_size    = 0;
}