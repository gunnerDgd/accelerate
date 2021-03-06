#pragma once
#include <accelerate/task/kernel/argument.hpp>

namespace accelerate::task::kernel {
	
	template <typename ArgumentType, typename... Remaining>
	std::tuple<argument<std::decay_t<ArgumentType>>, argument<std::decay_t<Remaining>>...>
		make_argument(execution::context& context, ArgumentType&& args, Remaining&&... remaining);

	template <typename ArgumentType>
	std::tuple<argument<std::decay_t<ArgumentType>>>
		make_argument(execution::context& context, ArgumentType&& args);
}

template <typename ArgumentType, typename... Remaining>
std::tuple<accelerate::task::kernel::argument<std::decay_t<ArgumentType>>, 
		   accelerate::task::kernel::argument<std::decay_t<Remaining>>...>
		   accelerate::task::kernel::make_argument(execution::context& context, ArgumentType&& args, Remaining&&... remaining)
{
	return std::tuple_cat(make_argument(context, args),
						  make_argument(context, remaining...));
}

template <typename ArgumentType>
std::tuple<accelerate::task::kernel::argument<std::decay_t<ArgumentType>>>
		   accelerate::task::kernel::make_argument(execution::context& context, ArgumentType&& args)
{
	return std::make_tuple(argument<std::decay_t<ArgumentType>>(context, args));
}