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
	template <typename ExpectedValueT>
	struct BeEquivalent
	{
		const ExpectedValueT & expected_value;
		
		template <typename ExaminerT, typename ValueT>
		bool operator()(ExaminerT & examiner, const ValueT & value)
		{
			examiner.check(value.equivalent(expected_value), *this);
		}
		
		std::ostream & operator<<(std::ostream & output)
		{
			return output << "be equivalent to " << Streams::safe(expected_value);
		}
	};
	
	template <typename ValueT>
	BeEquivalent<ValueT> be_equivalent(const ValueT & value)
	{
		return {value};
	}
}
