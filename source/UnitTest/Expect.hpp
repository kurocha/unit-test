//
//  Expect.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 29/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Examiner.hpp"

#include <iostream>

#include <Streams/Safe.hpp>
#include <Streams/Tuple.hpp>
#include <Streams/Container.hpp>

namespace UnitTest
{
	class Examiner;
	
	template <typename ParentT, typename ValueT>
	struct Expect;
	
	template <typename ParentT, typename ValueT>
	struct To
	{
		// It will always be of type Expect<...>
		ParentT & parent;
		const ValueT & value;
		
		template <typename FunctionT>
		bool check(bool condition, FunctionT function)
		{
			if (condition) {
				parent.pass();
			} else {
				parent.fail();
			}
			
			parent.check(condition == true, *this)
			
			assertions.assert(condition) << "Expected " << Streams::safe(value) << " to be " << function;
			
			return condition;
		}
		
		explicit operator bool() const noexcept
		{
			return assertions;
		}
		
		template <typename NestedValueT>
		auto expect(const NestedValueT & value) const noexcept
		{
			return make_expect(*this, value);
		}
		
	private:
		template <typename ParentT, typename NestedValueT>
		auto make_expect(ParentT & parent, const NestedValueT & value) const noexcept {
			return Expect<ParentT, NestedValueT>{*this, value, parent.depth + 1};
		}
	};
	
	template <typename ParentT, typename ValueT>
	struct Expect
	{
		// It can be either Examiner or To<...>
		ParentT & parent;
		const ValueT & value;
		Assertions & assertions;
		
		std::size_t depth = 0;
		
		template <typename FunctionT>
		void to(FunctionT function) const
		{
			to(true, function, value);
		}
		
		template <typename FunctionT>
		void to_not(FunctionT function) const
		{
			to(false, function, value);
		}
		
		template <typename FunctionT>
		void to_each(FunctionT function) const
		{
			for (const auto & item : value) {
				to(true, function, item);
			}
		}
		
		template <typename FunctionT>
		void to_each_not(FunctionT function) const
		{
			for (const auto & item : value) {
				to(false, function, item);
			}
		}
		
	private:
		template <typename ParentT, typename NestedValueT>
		auto make_to(ParentT & parent, const NestedValueT & value) const noexcept {
			return To<ParentT, NestedValueT>{*this, value};
		}
		
		template <typename FunctionT, typename NestedValueT>
		To<ValueT> to(bool expected, FunctionT function, const NestedValueT & nested_value) const noexcept
		{
			auto to = make_to(*this, nested_value);
			
			function(to);
			
			if (expected) {
				parent.check(to, to.assertions);
			} else {
				parent.check(!to, to.assertions);
			}
		}
	};
}
