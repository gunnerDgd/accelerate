#pragma once
#include <CL/cl.hpp>

#include <type_traits>
#include <string>

namespace accelerate::platform::query {
	struct profile
	{
		static constexpr std::size_t id = CL_PLATFORM_PROFILE;
		typedef			 std::string type;
	};

	struct version
	{
		static constexpr std::size_t id = CL_PLATFORM_VERSION;
		typedef			 std::string type;
	};

	struct vendor
	{
		static constexpr std::size_t id = CL_PLATFORM_NAME;
		typedef			 std::string type;
	};

	struct name
	{
		static constexpr std::size_t id = CL_PLATFORM_VENDOR;
		typedef			 std::string type;
	};
}

namespace accelerate::platform {

	inline constexpr query::profile profile;
	inline constexpr query::version version;
	inline constexpr query::vendor  vendor ;
	inline constexpr query::name    name   ;

	template <typename QueryType, typename ReturnType>
	using if_profile = std::enable_if_t<std::decay_t<QueryType>::id == query::profile::id, ReturnType>;

	template <typename QueryType, typename ReturnType>
	using if_version = std::enable_if_t<std::decay_t<QueryType>::id == query::version::id, ReturnType>;

	template <typename QueryType, typename ReturnType>
	using if_vendor  = std::enable_if_t<std::decay_t<QueryType>::id == query::vendor ::id, ReturnType>;

	template <typename QueryType, typename ReturnType>
	using if_name    = std::enable_if_t<std::decay_t<QueryType>::id == query::name   ::id, ReturnType>;
}