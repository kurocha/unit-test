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
#include <Streams/Tuple.hpp>
#include <Streams/Container.hpp>

#include "Expectation/ThrowException.hpp"

namespace UnitTest
{
	template <typename ExaminerT, typename ValueT>
	class Expectation
	{
	public:
		Expectation(ExaminerT & examiner, const ValueT & value, bool inverted = false) : _examiner(examiner), _value(value), _inverted(inverted) {}
		
		Expectation inverted() const noexcept {
			return Expectation(_examiner, _value, !_inverted);
		}
		
		auto to() const
		{
			return *this;
		}
		
		auto to_not() const
		{
			return this->inverted();
		}
		
		template <typename FunctionT>
		auto to(FunctionT function) const
		{
			return function(*this, _value);
		}
		
		template <typename FunctionT>
		auto to_not(FunctionT function) const
		{
			return function(this->inverted(), _value);
		}
		
#define UNITTEST_OPERATOR(op) \
		template <typename OtherT> \
		[[deprecated]] void operator op(const OtherT & other) const \
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
		void to_throw(ArgumentsT... arguments) const
		{
			to(throw_exception<ExceptionT>(arguments...));
		}
		
		template <typename FunctionT>
		void check(bool condition, FunctionT function) const
		{
			if (!_inverted) {
				_examiner << "Expected " << Streams::safe(_value) << " to " << function << std::endl;
				_examiner.check(condition);
			} else {
				_examiner << "Expected " << Streams::safe(_value) << " to not " << function << std::endl;
				_examiner.check(!condition);
			}
		}
		
	private:
		ExaminerT & _examiner;
		const ValueT & _value;
		
		bool _inverted;
	};
}
