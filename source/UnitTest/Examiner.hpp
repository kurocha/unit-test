//
//  Examiner.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Statistics.hpp"
#include "Expectation.hpp"

#include <iostream>
#include <sstream>

namespace UnitTest
{
	/// A examiner runs the tests and keeps track of the results.
	class Examiner
	{
		Statistics * _statistics;

		std::stringstream _buffer;
		std::ostream & _output;

	public:
		Examiner(Statistics * statistics, std::ostream & output = std::cerr);
		
		template <typename ValueT>
		Expectation<Examiner, ValueT> expect(const ValueT & value) {
			return {*this, value};
		}
		
		// Check if the condition is true, otherwise the test fails.
		void check(bool condition);
		
		template <typename LeftT, typename RightT>
		[[deprecated]] void check_equal(LeftT left, RightT right) {
			(*this) << left << " == " << right << std::endl;
			
			check(left == right);
		}

		template <typename ValueT>
		std::ostream & operator<< (ValueT && value)
		{
			return (_buffer << value);
		}
	};
}
