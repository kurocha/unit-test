//
//  BeOrdered.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace UnitTest
{
	namespace Expectations
	{
		struct BeOrdered
		{
			template <typename ValueT>
			void operator()(const ValueT & value, Assertions & assertions)
			{
				auto current = std::begin(value);
				auto end = std::end(value);
				
				auto previous = current;
				current++;
				
				while (current != end) {
					assertions.assert(previous <= current);
				}
			}
		};
	}
}
