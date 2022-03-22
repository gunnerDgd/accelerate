#include <accelerate/memory/unmapped/unmapped.hpp>

accelerate::memory::unmapped::~unmapped() { ::clReleaseMemObject(__M_unmapped_handle); }
accelerate::memory::unmapped::unmapped (unmapped& copy) : __M_unmapped_handle  (copy.__M_unmapped_handle)  ,
														  __M_unmapped_size    (copy.__M_unmapped_size)    ,
														  __M_unmapped_executor(copy.__M_unmapped_executor)
{
	::clRetainMemObject(__M_unmapped_handle);
}

accelerate::memory::unmapped::unmapped(unmapped&& move) : __M_unmapped_handle  (move.__M_unmapped_handle)  ,
														  __M_unmapped_size    (move.__M_unmapped_size)	   ,
														  __M_unmapped_executor(move.__M_unmapped_executor)
{
	move.__M_unmapped_handle = invalid_handle;
}

typename accelerate::memory::unmapped::native_handle_type 
		 accelerate::memory::unmapped::native_handle()   { return __M_unmapped_handle; }

typename accelerate::memory::unmapped::size_type 
		 accelerate::memory::unmapped::size()			 { return __M_unmapped_size  ; }