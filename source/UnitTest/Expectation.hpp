//
//  Expectation.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 12/7/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#pragma once

// Expectation operators below have side effects. We disable superfluous warnings.
// #pragma clang diagnostic ignored "-Wunused-comparison"

#include <iostream>
#include <typeinfo>

namespace UnitTest
{
	std::ostream & operator<< (std::ostream & out, const std::type_info & rhs);
	std::ostream & operator<< (std::ostream & out, const std::nullptr_t &);
	
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
		
#undef UNITTEST_OPERATOR
		
		template <typename ExceptionT, typename... ArgumentsT>
		void to_throw(ArgumentsT... arguments) {
			try {
				_examiner << "Expected " << typeid(_value).name() << " to throw " << typeid(ExceptionT).name() << std::endl;
				_value(arguments...);
				_examiner.check(false);
			} catch (ExceptionT & exception) {
				_examiner.check(true);
			}
		}
		
	private:
		ExaminerT & _examiner;
		const ValueT & _value;
	};
}
