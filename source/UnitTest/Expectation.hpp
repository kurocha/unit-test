//
//  Expectation.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 12/7/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#pragma once

#include <iostream>
#include <typeinfo>

#include <Streams/Safe.hpp>

namespace UnitTest
{
	template <typename ExaminerT, typename ValueT>
	class Expectation
	{
	public:
		Expectation(ExaminerT & examiner, const ValueT & value, bool inverted = false) : _examiner(examiner), _value(value), _inverted(inverted) {}
		
		Expectation to_not() const noexcept {
			return Expectation(_examiner, _value, !_inverted);
		}
		
		template <typename FunctionT>
		struct Condition
		{
			const FunctionT & apply;
		};
		
#define UNITTEST_OPERATOR(op) \
		template <typename OtherT> \
		void operator op(const OtherT & other) const \
		{ \
			if (_inverted == false) { \
				_examiner << "Expected " << Streams::safe(_value) << " to be " << #op << ' ' << Streams::safe(other) << std::endl; \
				_examiner.check(_value op other); \
			} else { \
				_examiner << "Expected " << Streams::safe(_value) << " to not be " << #op << ' ' << Streams::safe(other) << std::endl; \
				_examiner.check(!(_value op other)); \
			}\
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
				_examiner << "Expected " << Streams::safe(typeid(_value)) << " to throw " << Streams::safe(typeid(ExceptionT)) << std::endl;
				_value(arguments...);
				_examiner.check(_inverted);
			} catch (ExceptionT & exception) {
				_examiner.check(!_inverted);
			}
		}
		
	private:
		ExaminerT & _examiner;
		const ValueT & _value;
		
		bool _inverted;
	};
}
