//
//  Be.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "../Expectation.hpp"

namespace UnitTest
{
	template <typename LeftT, typename RightT>
	struct BeAnd
	{
		const LeftT & left;
		const RightT & right;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			left(examiner, value);
			right(examiner, value);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeAnd & condition)
		{
			return output << condition.left << " and " << condition.right;
		}
	};
	
	template <typename LeftT, typename RightT>
	BeAnd<LeftT, RightT> be_and(const LeftT & left, const RightT & right)
	{
		return {left, right};
	}
	
	template <typename LeftT, typename RightT>
	struct BeOr
	{
		const LeftT & left;
		const RightT & right;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			left(examiner, value);
			right(examiner, value);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeOr & condition)
		{
			return output << condition.left << " or " << condition.right;
		}
	};
	
	template <typename LeftT, typename RightT>
	BeOr<LeftT, RightT> be_or(const LeftT & left, const RightT & right)
	{
		return {left, right};
	}
	
	template <typename ExpectedValueT>
	struct BeEqual
	{
		const ExpectedValueT & expected_value;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			examiner.check(value == expected_value, *this);
		}
		
		template <typename RightT>
		auto operator&&(const RightT & right)
		{
			return be_and(*this, right);
		}
		
		template <typename RightT>
		auto operator||(const RightT & right)
		{
			return be_or(*this, right);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeEqual & condition)
		{
			return output << "be == " << Streams::safe(condition.expected_value);
		}
	};
	
	template <typename ExpectedValueT>
	struct BeNotEqual
	{
		const ExpectedValueT & expected_value;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			examiner.check(value != expected_value, *this);
		}
		
		template <typename RightT>
		auto operator&&(const RightT & right)
		{
			return be_and(*this, right);
		}
		
		template <typename RightT>
		auto operator||(const RightT & right)
		{
			return be_or(*this, right);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeNotEqual & condition)
		{
			return output << "be != " << Streams::safe(condition.expected_value);
		}
	};
	
	template <typename ExpectedValueT>
	struct BeLessThan
	{
		const ExpectedValueT & expected_value;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			examiner.check(value < expected_value, *this);
		}
		
		template <typename RightT>
		auto operator&&(const RightT & right)
		{
			return be_and(*this, right);
		}
		
		template <typename RightT>
		auto operator||(const RightT & right)
		{
			return be_or(*this, right);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeLessThan & condition)
		{
			return output << "be < " << Streams::safe(condition.expected_value);
		}
	};
	
	template <typename ExpectedValueT>
	struct BeLessThanOrEqual
	{
		const ExpectedValueT & expected_value;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			examiner.check(value <= expected_value, *this);
		}
		
		template <typename RightT>
		auto operator&&(const RightT & right)
		{
			return be_and(*this, right);
		}
		
		template <typename RightT>
		auto operator||(const RightT & right)
		{
			return be_or(*this, right);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeLessThanOrEqual & condition)
		{
			return output << "be <= " << Streams::safe(condition.expected_value);
		}
	};
	
	template <typename ExpectedValueT>
	struct BeGreaterThan
	{
		const ExpectedValueT & expected_value;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			examiner.check(value > expected_value, *this);
		}
		
		template <typename RightT>
		auto operator&&(const RightT & right)
		{
			return be_and(*this, right);
		}
		
		template <typename RightT>
		auto operator||(const RightT & right)
		{
			return be_or(*this, right);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeGreaterThan & condition)
		{
			return output << "be > " << Streams::safe(condition.expected_value);
		}
	};
	
	template <typename ExpectedValueT>
	struct BeGreaterThanOrEqual
	{
		const ExpectedValueT & expected_value;
		
		template <typename ExaminerT, typename ValueT>
		void operator()(const ExaminerT & examiner, const ValueT & value) const
		{
			examiner.check(value >= expected_value, *this);
		}
		
		template <typename RightT>
		auto operator&&(const RightT & right)
		{
			return be_and(*this, right);
		}
		
		template <typename RightT>
		auto operator||(const RightT & right)
		{
			return be_or(*this, right);
		}
		
		friend std::ostream & operator<<(std::ostream & output, BeGreaterThanOrEqual & condition)
		{
			return output << "be >= " << Streams::safe(condition.expected_value);
		}
	};
	
	struct Be
	{
		template <typename ExpectedValueT>
		BeEqual<ExpectedValueT> operator==(const ExpectedValueT & expected_value)
		{
			return {expected_value};
		}
		
		template <typename ExpectedValueT>
		BeNotEqual<ExpectedValueT> operator!=(const ExpectedValueT & expected_value)
		{
			return {expected_value};
		}
		
		template <typename ExpectedValueT>
		BeLessThan<ExpectedValueT> operator<(const ExpectedValueT & expected_value)
		{
			return {expected_value};
		}
		
		template <typename ExpectedValueT>
		BeLessThanOrEqual<ExpectedValueT> operator<=(const ExpectedValueT & expected_value)
		{
			return {expected_value};
		}
		
		template <typename ExpectedValueT>
		BeGreaterThan<ExpectedValueT> operator>(const ExpectedValueT & expected_value)
		{
			return {expected_value};
		}
		
		template <typename ExpectedValueT>
		BeGreaterThanOrEqual<ExpectedValueT> operator>=(const ExpectedValueT & expected_value)
		{
			return {expected_value};
		}
	};
	
	extern Be be;
}
