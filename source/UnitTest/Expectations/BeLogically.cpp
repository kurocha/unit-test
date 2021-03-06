//
//  BeLogically.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "BeLogically.hpp"

namespace UnitTest
{
	namespace Expectations
	{
		std::ostream & operator<<(std::ostream & output, const BeLogically & condition)
		{
			return output << "be logically " << Format::variable(condition.expected_value);
		}
		
		BeLogically be_true = {true};
		BeLogically be_false = {false};
		
		BeLogically be_logically(bool value)
		{
			return {value};
		}
	}
}
