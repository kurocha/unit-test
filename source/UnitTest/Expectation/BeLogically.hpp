//
//  BeLogically.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "../Expectation.hpp"

namespace UnitTest
{
	struct BeLogically
	{
		bool expected_value;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value)
		{
			examiner.check(static_cast<bool>(value) == true, *this);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeLogically & condition);
	};
	
	extern BeLogically be_true;
	extern BeLogically be_false;
	BeLogically be_logically(bool value);
}
