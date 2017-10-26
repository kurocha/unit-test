//
//  ThrowException.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace UnitTest
{
	// Use std::apply when updating to C++17.
	namespace
	{
		template <class F, class Tuple, std::size_t... I>
		constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
		{
			return f(std::get<I>(std::forward<Tuple>(t))...);
		}
		
		template <class F, class Tuple>
		constexpr decltype(auto) apply(F&& f, Tuple&& t)
		{
			return apply_impl(
				std::forward<F>(f), std::forward<Tuple>(t),
				std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{}
			);
		}
	}
	
	template <typename ExceptionT, typename ...ArgumentsT>
	struct ThrowException
	{
		std::tuple<ArgumentsT...> arguments;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value)
		{
			try {
				apply(value, arguments);
				examiner.check(false, *this);
			} catch (ExceptionT & exception) {
				examiner.check(true, *this);
			}
		}
		
		friend std::ostream & operator<<(std::ostream & output, ThrowException &)
		{
			return output << "throw exception " << Streams::safe(typeid(ExceptionT));
		}
	};
	
	template <typename ExceptionT, typename ...ArgumentsT>
	ThrowException<ExceptionT> throw_exception(ArgumentsT ...arguments)
	{
		return {std::make_tuple(arguments...)};
	}
}
