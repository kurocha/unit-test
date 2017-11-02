//
//  BeEquivalent.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace UnitTest
{
	namespace Expectations
	{
		template <typename ExpectedValueT>
		struct BeEquivalent
		{
			const ExpectedValueT & expected_value;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions)
			{
				return assertions.assert(value.equivalent(expected_value), *this);
			}
			
			friend std::ostream & operator<<(std::ostream & output, const BeEquivalent & condition)
			{
				return output << "be equivalent to " << Format::variable(condition.expected_value);
			}
		};
		
		template <typename ValueT>
		BeEquivalent<ValueT> be_equivalent(const ValueT & value)
		{
			return {value};
		}
	}
}
