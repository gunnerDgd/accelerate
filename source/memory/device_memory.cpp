#include <accelerate/memory/memory.hpp>

accelerate::memory::device_memory::device_memory(executor_type& exec, native_handle_type hnd)
	: __M_devmem_executor(exec),
	  __M_devmem_handle  (hnd)					   { ::clRetainMemObject(hnd); }

accelerate::memory::device_memory::device_memory(const device_memory& copy)
	: __M_devmem_executor(copy.__M_devmem_executor),
	  __M_devmem_handle  (copy.__M_devmem_handle)  { ::clRetainMemObject(__M_devmem_handle); }

accelerate::memory::device_memory::device_memory(const device_memory&& move)
	: __M_devmem_executor(move.__M_devmem_executor),
	  __M_devmem_handle  (move.__M_devmem_handle)  {  }

typename accelerate::memory::device_memory::native_handle_type 
		 accelerate::memory::device_memory::native_handle()  { return __M_devmem_handle  ; }

typename accelerate::memory::device_memory::executor_type& 
		 accelerate::memory::device_memory::get_executor()   { return __M_devmem_executor; }