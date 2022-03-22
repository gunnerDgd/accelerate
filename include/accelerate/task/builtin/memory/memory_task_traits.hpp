#pragma once
namespace accelerate::task::category {
	struct memory_task						 {};
	struct read_memory  : public memory_task {};
	struct write_memory : public memory_task {};
}

namespace accelerate::task {
	inline constexpr category::read_memory  read_operation ;
	inline constexpr category::write_memory write_operation;
}