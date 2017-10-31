//
//  BeLogically.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "../Expect.hpp"

namespace UnitTest
{
	namespace Expectations
	{
		struct BeLogically
		{
			bool expected_value;
			
			template <typename ValueT>
			void operator()(To<ValueT> & to)
			{
				to.check(static_cast<bool>(to.value) == expected_value, *this);
			}
			
			friend std::ostream & operator<<(std::ostream & output, const BeLogically & condition);
		};
		
		extern BeLogically be_true;
		extern BeLogically be_false;
		BeLogically be_logically(bool value);
	}
}
