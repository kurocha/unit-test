//
//  Expect.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 29/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Assertions.hpp"
#include "Expectations/Be.hpp"
#include "Expectations/ThrowException.hpp"

#include <iostream>

#include "Format.hpp"

namespace UnitTest
{
	template <typename ValueT>
	struct Expect;
	
	template <typename FunctionT, typename ValueT>
	struct To
	{
		const FunctionT function;
		const ValueT value;
		
		bool inverted;
		
		void operator()(Assertions & assertions) const
		{
			function(value, assertions);
		}
		
		friend std::ostream & operator<<(std::ostream & output, const To & to)
		{
			return output << "Expected " << Format::variable(to.value) << (to.inverted ? " to not " : " to ") << to.function;
		}
	};
	
	template <typename ValueT>
	struct Expect
	{
		Assertions & assertions;
		const ValueT value;
		
		template <typename FunctionT>
		void to(FunctionT && function) const
		{
			to(false, std::forward<FunctionT>(function), value);
		}
		
		template <typename FunctionT>
		void to_not(FunctionT && function) const
		{
			to(true, std::forward<FunctionT>(function), value);
		}
		
		template <typename FunctionT>
		void to_each(FunctionT && function) const
		{
			for (const auto & item : value) {
				to(false, std::forward<FunctionT>(function), item);
			}
		}
		
		template <typename FunctionT>
		void to_each_not(FunctionT && function) const
		{
			for (const auto & item : value) {
				to(true, std::forward<FunctionT>(function), item);
			}
		}
		
		template <typename OtherT>
		void operator==(const OtherT & other) {to(Expectations::be == other);}
		
		template <typename OtherT>
		void operator!=(const OtherT & other) {to(Expectations::be != other);}
		
		template <typename OtherT>
		void operator<(const OtherT & other) {to(Expectations::be < other);}
		
		template <typename OtherT>
		void operator<=(const OtherT & other) {to(Expectations::be <= other);}
		
		template <typename OtherT>
		void operator>(const OtherT & other) {to(Expectations::be > other);}
		
		template <typename OtherT>
		void operator>=(const OtherT & other) {to(Expectations::be >= other);}
		
		template <typename ExceptionT, typename ...ArgumentsT>
		void to_throw(ArgumentsT ...arguments) {to(Expectations::throw_exception<ExceptionT>(arguments...));}
		
	private:
		template <typename FunctionT, typename NestedValueT>
		void to(bool inverted, FunctionT && function, NestedValueT && nested_value) const noexcept
		{
			To<FunctionT, NestedValueT> to{function, nested_value, inverted};
			
			if (inverted)
				assertions.refute(to);
			else
				assertions.assert(to);
		}
	};
}
