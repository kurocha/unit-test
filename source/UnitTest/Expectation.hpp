//
//  Expectation.hpp
//  File file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 12/7/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#ifndef UNITTEST_EXPECTATION_H
#define UNITTEST_EXPECTATION_H

#pragma clang diagnostic ignored "-Wunused-comparison"

#include <iostream>

namespace UnitTest
{
	template <typename ExaminerT, typename ValueT>
	class Expectation
	{
	public:
		Expectation(ExaminerT & examiner, const ValueT & value) : _examiner(examiner), _value(value) {}
		
		template <typename FunctionT>
		struct Condition
		{
			const FunctionT & apply;
		};
		
#define UNITTEST_OPERATOR(op) \
		template <typename OtherT> \
		void operator op(const OtherT & other) const \
		{ \
			_examiner << "Expected " << _value << ' ' << #op << ' ' << other << std::endl; \
			_examiner.check(_value op other); \
		}
		
		UNITTEST_OPERATOR(==)
		UNITTEST_OPERATOR(!=)
		UNITTEST_OPERATOR(<)
		UNITTEST_OPERATOR(<=)
		UNITTEST_OPERATOR(>=)
		UNITTEST_OPERATOR(>)
		
	private:
		ExaminerT & _examiner;
		const ValueT & _value;
	};
}

#endif
