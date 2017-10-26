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

namespace UnitTest
{
	namespace {
		template <class F, class Tuple, std::size_t... I>
		constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
		{
			return f(std::get<I>(std::forward<Tuple>(t))...);
		}
		
		template <class F, class Tuple>
		constexpr decltype(auto) apply(F&& f, Tuple&& t)
		{
			return apply_impl(
				std::forward<F>(f), std::forward<Tuple>(t),
				std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{}
			);
		}
	}
	
	template <typename ExceptionT, typename ...ArgumentsT>
	struct ThrowException
	{
		std::tuple<ArgumentsT...> arguments;
		
		template <typename ExaminerT, typename ValueT>
		bool operator()(ExaminerT & examiner, const ValueT & value)
		{
			try {
				// Use std:: when updating to C++17.
				apply(value, arguments);
				examiner.check(false, *this);
			} catch (ExceptionT & exception) {
				examiner.check(true, *this);
			}
		}
		
		std::ostream & operator<<(std::ostream & output)
		{
			output << "throw exception " << Streams::safe(typeid(ExceptionT));
		}
	};
	
	template <typename ExceptionT, typename ...ArgumentsT>
	ThrowException<ExceptionT> throw_exception(ArgumentsT ...arguments)
	{
		return {std::make_tuple(arguments...)};
	}
	
	// expect(...).to(throw_exception<MyException>());
	// expect(...).to(be_equivalent(5.0));
	// expect(...).to(be_within(1.0).of(10.0));
	// expect(...).to_not(be_between(5.0, 10.0));
	// 
	// expect(...).to<BeWithin>()
	
	template <typename ExaminerT, typename ValueT>
	class Expectation
	{
	public:
		Expectation(ExaminerT & examiner, const ValueT & value, bool inverted = false) : _examiner(examiner), _value(value), _inverted(inverted) {}
		
		Expectation inverted() const noexcept {
			return Expectation(_examiner, _value, !_inverted);
		}
		
		auto to()
		{
			return *this;
		}
		
		auto to_not()
		{
			return this->inverted();
		}
		
		template <typename FunctionT>
		auto to(FunctionT function)
		{
			return function(*this);
		}
		
		template <typename FunctionT>
		auto to_not(FunctionT function)
		{
			return function(*this);
		}
		
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
		void to_throw(ArgumentsT... arguments)
		{
			to(throw_exception<ExceptionT>(arguments...));
		}
		
		template <typename FunctionT>
		void check(bool condition, FunctionT function) {
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
