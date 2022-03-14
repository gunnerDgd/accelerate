#pragma once
#include <accelerate/execution/context.hpp>
#include <accelerate/memory/memory_traits.hpp>

namespace accelerate::memory {
	template <typename AccessMode>
	class unmapped_memory
	{
	public:
		using native_handle_type = ::cl_mem;
		using size_type			 = std::size_t;

		unmapped_memory (execution::context&, size_type);
		~unmapped_memory();

	private:
		native_handle_type __M_unmap_handle;
	};

	using rdonly_unmapped = unmapped_memory<access_type::read_only>;
	using wronly_unmapped = unmapped_memory<access_type::read_only>;
}