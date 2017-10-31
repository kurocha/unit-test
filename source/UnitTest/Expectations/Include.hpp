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
			bool operator()(To<ValueT> & to)
			{
				auto begin = std::begin(to.value);
				auto end = std::end(to.value);
				
				return to.check(std::find(begin, end, needle) != end, *this);
			}
			
			bool operator()(To<std::string> & to)
			{
				auto pos = to.value.find(needle);
				
				return to.check(pos != std::string::npos, *this);
			}
			
			friend std::ostream & operator<<(std::ostream & output, const Include & condition)
			{
				return output << "include " << Streams::safe(condition.needle);
			}
		};
		
		template <typename ValueT>
		Include<ValueT> include(const ValueT & value)
		{
			return {value};
		}
	}
}
