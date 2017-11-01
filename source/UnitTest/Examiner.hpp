//
//  Examiner.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <iostream>
#include <sstream>

#include "Assertions.hpp"
#include "Expect.hpp"

#include "Expectations/Be.hpp"
#include "Expectations/BeLogically.hpp"

namespace UnitTest
{
	/// A examiner runs the tests and keeps track of the results.
	class Examiner
	{
		Assertions & _assertions;
		
	public:
		Examiner(Assertions & assertions) : _assertions(assertions) {};
		
		template <typename ValueT>
		Expect<ValueT> expect(const ValueT & value) {
			return {_assertions, value};
		}
		
		// Check if the condition is true, otherwise the test fails.
		[[deprecated]] void check(bool condition)
		{
			expect(condition).to(Expectations::be_true);
		}

		template <typename LeftT, typename RightT>
		[[deprecated]] void check_equal(LeftT left, RightT right) {
			expect(left).to(Expectations::be == right);
		}
		
		template <typename ValueT>
		std::ostream & operator<< (ValueT && value)
		{
			return _assertions.output() << value;
		}
	};
}
