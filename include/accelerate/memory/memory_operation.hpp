#pragma once
#include <accelerate/execution/executor.hpp>
#include <accelerate/task/builtin/memory/memory_task.hpp>

namespace accelerate::memory {
	template <typename MemoryObject, typename ReadType>
	void read_from(execution::executor&, MemoryObject&&, ReadType&);
	template <typename MemoryObject, typename ReadType, std::size_t ReadCount>
	void read_from(execution::executor&, MemoryObject&&, ReadType(&)[ReadCount]);
	
	template <typename MemoryObject, typename WriteType>
	void write_to (execution::executor&, MemoryObject&&, WriteType&&);
	template <typename MemoryObject, typename WriteType, std::size_t WriteCount>
	void write_to (execution::executor&, MemoryObject&&, WriteType(&)[WriteCount]);
}

template <typename MemoryObject, typename ReadType>
void accelerate::memory::read_from(execution::executor& exec, MemoryObject&& memobj, ReadType& rdbuf)
{
	task::builtin::read_memory read_task(memobj, rdbuf);
	exec			.dispatch (read_task);
}
template <typename MemoryObject, typename ReadType, std::size_t ReadCount>
void accelerate::memory::read_from(execution::executor& exec, MemoryObject&& memobj, ReadType(&rdbuf)[ReadCount])
{
	task::builtin::read_memory read_task(memobj, rdbuf);
	exec			.dispatch (read_task);
}

template <typename MemoryObject, typename WriteType>
void accelerate::memory::write_to(execution::executor& exec, MemoryObject&& memobj, WriteType&& wrbuf)
{
	task::builtin::write_memory write_task(memobj, wrbuf);
	exec 			  .dispatch(write_task);
}

template <typename MemoryObject, typename WriteType, std::size_t WriteCount>
void accelerate::memory::write_to(execution::executor& exec, MemoryObject&& memobj, WriteType(&wrbuf)[WriteCount])
{
	task::builtin::write_memory write_task(memobj, wrbuf);
	exec 			  .dispatch(write_task);
}