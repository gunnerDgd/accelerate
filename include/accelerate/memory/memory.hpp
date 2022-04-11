#pragma once
#include <accelerate/execution/executor.hpp>
#include <accelerate/memory/declare.hpp>

namespace accelerate::memory {
	class device_memory
	{
	public:
		using size_type		  = ::cl_uint;
		using difference_type = ::cl_int ;
		using executor_type   = execution::executor;

		using					native_handle_type				  = ::cl_mem;
		static inline constexpr native_handle_type invalid_handle = nullptr ;

		template <typename MemoryType, size_type MemorySize>
		class mapped;
		template <typename MemoryType, size_type MemorySize>
		class unmapped;
	
	private:
		device_memory(executor_type&, native_handle_type);
	public:
		device_memory(const device_memory&);
		device_memory(const device_memory&&);

		native_handle_type native_handle();
		executor_type&     get_executor ();

	private:
		native_handle_type __M_devmem_handle  ;
		executor_type&     __M_devmem_executor;
	};
}