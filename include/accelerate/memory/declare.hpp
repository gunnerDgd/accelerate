#pragma once
#include <accelerate/memory/memory_traits.hpp>

namespace accelerate::memory {
	template <typename MemoryType, types::size_type MemoryCount = 1> class unmapped;
	template <typename MemoryType, types::size_type MemoryCount = 1> class mapped  ;
}

namespace accelerate::memory::adapter {
	template <typename AccessType>   class		  pointer ;
	template <typename VariableType> class		  variable;
	template <typename VariableType> class mapped_variable;
}