#pragma once
#include <CL/cl.hpp>

#include <type_traits>
#include <filesystem>
#include <string_view>

namespace accelerate::build::options {
	using namespace std::string_literals;

	struct build_option						  {};
	struct preprocessor : public build_option {};
	struct intrinsics   : public build_option {};
	struct optimization : public build_option {};

	struct predefine : public preprocessor
	{
		predefine(std::string def)					: __M_predef_str("-D "s + def + " "s) { }
		predefine(std::string def, std::string ctx) : __M_predef_str("-D "s + def + "="s + ctx + " "s) {}

		std::string to_string() { return __M_predef_str; }

	private:
		std::string __M_predef_str;
	};

	struct include_path : public preprocessor
	{
		include_path		 (std::filesystem::directory_entry ent) : __M_include_dirent(ent.path().string()) {}
		std::string to_string() { return __M_include_dirent; }
	private:
		std::string __M_include_dirent;
	};

	struct single_precision_constant : public intrinsics   { static constexpr const char* option = "-cl-single-precision-constant "; };
	struct denorms_zero				 : public intrinsics   { static constexpr const char* option = "-cl-denorms-are-zero"; };
	
	struct disable_optimization		 : public optimization { static constexpr const char* option = "-cl-opt-disable"; };
	struct strict_aliasing			 : public optimization { static constexpr const char* option = "-cl-strict-optimizing"; };
	struct enable_mad				 : public optimization { static constexpr const char* option = "-cl-mad-enable"; };
	struct no_signed_zero			 : public optimization { static constexpr const char* option = "-cl-no-signed-zeros"; };
	struct unsafe_math_optimization  : public optimization { static constexpr const char* option = "-cl-unsafe-math-optimizations"; };
	struct finite_math_only			 : public optimization { static constexpr const char* option = "-cl-finite-math-only"; };	
}

namespace accelerate::build {

	inline constexpr options::single_precision_constant  single_precision_constant{};
	inline constexpr options::denorms_zero				 denorms_zero			  {};

	inline constexpr options::disable_optimization		 disable_optimization	  {};
	inline constexpr options::strict_aliasing			 strict_aliasing		  {};
	inline constexpr options::enable_mad				 enable_mad				  {};
	inline constexpr options::no_signed_zero			 no_signed_zero			  {};
	inline constexpr options::unsafe_math_optimization   unsafe_math_optimization {};
	inline constexpr options::finite_math_only			 finite_math_only		  {};
}