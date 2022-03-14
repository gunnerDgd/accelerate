#pragma once
#include <accelerate/execution/context.hpp>
#include <accelerate/memory/memory_traits.hpp>

namespace accelerate::memory {
	template <typename AccessMode>
	class mapped_memory
	{
	public:
		using native_handle_type = ::cl_mem;
		using size_type			 = std::size_t;

		template <typename AccessType, typename MapHandle>
		static std::enable_if_t<!std::is_base_of_v<access_type::access_mode, AccessType>, mapped_memory<AccessType>>
			make_mapped() {}

		template <typename AccessType, typename MapHandle>
		static std::enable_if_t<std::is_base_of_v<access_type::access_mode, AccessType>, mapped_memory<AccessType>>
			make_mapped(AccessType, MapHandle&& map_hnd, execution::context& ctx)
		{
			native_handle_type				 map_hnd = ::clCreateBuffer(ctx.native_handle(), AccessType::value, map_hnd.size(), map_hnd.address(), nullptr);
			return mapped_memory<AccessType>(map_hnd);
		}

	private:
		mapped_memory(native_handle_type);
	private:
		native_handle_type __M_mapped_handle;
	};
}