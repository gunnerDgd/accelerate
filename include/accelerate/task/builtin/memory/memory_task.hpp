#pragma once
#include <CL/cl.h>

#include <accelerate/task/declare.hpp>
#include <accelerate/task/builtin/memory/memory_task_traits.hpp>

#include <accelerate/execution/declare.hpp>
#include <memory/region/region.hpp>

namespace accelerate::task::builtin {
	class read_memory
	{
		friend class execution::executor;
	public:
		using native_memory_type = ::cl_mem;
		using pointer_type	     = void*;
		
		using size_type			 = std::size_t;
		using difference_type    = std::ptrdiff_t;

	public:
		template <typename ReadClMemory, typename ReadMemory, typename ReadRange>
		read_memory(ReadClMemory&&, ReadMemory&&, ReadRange);

	private:
		difference_type __M_rd_begin, __M_rd_end;
		size_type	    __M_rd_size;

		native_memory_type __M_rd_clmem;
		pointer_type	   __M_rd_mem  ;
	};

	class write_memory
	{
		friend class execution::executor;
	public:
		using native_memory_type = ::cl_mem;
		using pointer_type	     = void*;
		
		using size_type			 = std::size_t;
		using difference_type    = std::ptrdiff_t;

	public:
		template <typename WriteClMemory, typename WriteMemory, typename WriteRange>
		write_memory(WriteClMemory&&, WriteMemory&&, WriteRange);

	private:
		difference_type __M_wr_begin, __M_wr_end;
		size_type	    __M_wr_size;

		native_memory_type __M_wr_clmem;
		pointer_type	   __M_wr_mem  ;
	};
}

template <typename ReadClMemory, typename ReadMemory, typename ReadRange>
accelerate::task::builtin::read_memory::read_memory(ReadClMemory&& rd_clmem, ReadMemory&& rd_mem, ReadRange)
	: __M_rd_clmem(rd_clmem.native_handle()),
	  __M_rd_mem  (rd_mem  .address())		,
	  __M_rd_begin(memory::region::begin_v<ReadRange>),
	  __M_rd_end  (memory::region::end_v  <ReadRange>),
	  __M_rd_size (memory::region::end_v<ReadRange> - memory::region::end_v<ReadRange>) {  }

template <typename WriteClMemory, typename WriteMemory, typename WriteRange>
accelerate::task::builtin::write_memory::write_memory(WriteClMemory&& wr_clmem, WriteMemory&& wr_mem, WriteRange)
	: __M_wr_clmem(wr_clmem.native_handle()),
	  __M_wr_mem  (wr_mem  .address())		,
	  __M_wr_begin(memory::region::begin_v<WriteRange>),
	  __M_wr_end  (memory::region::end_v  <WriteRange>),
	  __M_wr_size (memory::region::end_v<WriteRange> - memory::region::end_v<WriteRange>) {  }