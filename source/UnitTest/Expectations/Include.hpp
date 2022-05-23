//
//  Include.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <algorithm>

namespace UnitTest
{
	namespace Expectations
	{
		template <typename NeedleT>
		struct Include
		{
			const NeedleT & needle;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				auto begin = std::begin(value);
				auto end = std::end(value);
				
				return assertions.test(std::find(begin, end, needle) != end, *this);
			}
			
			bool operator()(const std::string & value, Assertions & assertions) const
			{
				auto pos = value.find(needle);
				
				return assertions.test(pos != std::string::npos, *this);
			}
			
			friend std::ostream & operator<<(std::ostream & output, const Include & condition)
			{
				return output << "include " << Format::variable(condition.needle);
			}
		};
		
		template <typename ValueT>
		Include<ValueT> include(const ValueT & value)
		{
			return {value};
		}
	}
}
