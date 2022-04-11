#pragma once
#include <accelerate/device/device.hpp>
#include <accelerate/execution/context.hpp>

#define ACCELERATE_BUILD_DEFINE_CLASS(name) class name;

#define ACCELERATE_BUILD_TARGET_FRIEND friend class builder;\
									   friend class program;

#define ACCELERATE_BUILD_SOUCE_FRIEND  friend class program;\
									   friend class builder;\
									   friend class target ;

namespace accelerate::build {
	ACCELERATE_BUILD_DEFINE_CLASS(builder);
	ACCELERATE_BUILD_DEFINE_CLASS(target) ;
	ACCELERATE_BUILD_DEFINE_CLASS(source) ;
	ACCELERATE_BUILD_DEFINE_CLASS(binary) ;
}