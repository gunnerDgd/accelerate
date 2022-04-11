#pragma once
#include <accelerate/execution/executor.hpp>
#include <accelerate/task/event/event.hpp>

#include <accelerate/memory/memory.hpp>

namespace accelerate::memory {
	template <typename MemoryObject, typename ReadType>
	std::enable_if_t<std::is_same_v<device_memory, std::decay_t<MemoryObject>>, task::event>
		async_read_from(MemoryObject&&, ReadType&);

	template <typename MemoryObject, typename ReadType>
	std::enable_if_t<std::is_same_v<device_memory, std::decay_t<MemoryObject>>>
		read_from	   (MemoryObject&&, ReadType&);
	
	template <typename MemoryObject, typename WriteType>
	std::enable_if_t<std::is_same_v<device_memory, std::decay_t<MemoryObject>>>
		write_to	   (MemoryObject&&, WriteType&&);

	template <typename MemoryObject, typename WriteType>
	std::enable_if_t<std::is_same_v<device_memory, std::decay_t<MemoryObject>>, task::event>
		async_write_to (MemoryObject&&, WriteType&&);
}

template <typename MemoryObject, typename ReadType>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::decay_t<MemoryObject>>>
								accelerate::memory::read_from(MemoryObject&& memobj, ReadType& rdbuf)
{
	auto rd_memhnd  = memobj.native_handle();
	auto rd_memexec = memobj.get_executor ().native_handle();

	::clEnqueueReadBuffer(rd_memexec, rd_memhnd, true, 0, sizeof(ReadType), &rdbuf, 0, nullptr, nullptr);
}

template <typename MemoryObject, typename ReadType>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::decay_t<MemoryObject>>, accelerate::task::event>
								accelerate::memory::async_read_from(MemoryObject&& memobj, ReadType& rdbuf)
{
	task::event::native_handle_type rd_event;
	auto							rd_memhnd  = memobj.native_handle();
	auto							rd_memexec = memobj.get_executor().native_handle();

	::clEnqueueReadBuffer(rd_memexec, rd_memhnd, true, 0, sizeof(ReadType), &rdbuf, 0, nullptr, &rd_event); 
	return  task::event  (rd_event);
}

template <typename MemoryObject, typename WriteType>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::decay_t<MemoryObject>>>
								accelerate::memory::write_to(MemoryObject&& memobj, WriteType&& wrbuf)
{
	auto wr_memhnd  = memobj.native_handle();
	auto wr_memexec = memobj.get_executor ().native_handle();

	::clEnqueueWriteBuffer(wr_memexec, wr_memhnd, true, 0, sizeof(WriteType), &wrbuf, 0, nullptr, nullptr);
}

template <typename MemoryObject, typename WriteType>
std::enable_if_t<std::is_same_v<accelerate::memory::device_memory, std::decay_t<MemoryObject>>, accelerate::task::event>
								accelerate::memory::async_write_to(MemoryObject&& memobj, WriteType&& wrbuf)
{
	task::event::native_handle_type wr_event;
	auto							wr_memhnd  = memobj.native_handle();
	auto							wr_memexec = memobj.get_executor ().native_handle();

	::clEnqueueWriteBuffer(wr_memexec, wr_memhnd, true, 0, sizeof(WriteType), &wrbuf, 0, nullptr, &wr_event); 
	return	   task::event(wr_event);
}