//
//  Be.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "../Assertions.hpp"

#include <Streams/Safe.hpp>

namespace UnitTest
{
	namespace Expectations
	{
		// In theory this could work, but in practice it's messy due to opeartor precedence.
		// template <typename RightT>
		// struct BeNot
		// {
		// 	const RightT & right;
		// 	
		// 	template <typename ValueT>
		// 	bool operator()(const ValueT & value, Assertions & assertions) const
		// 	{
		// 		return assertions.refute([&value, this](Assertions & assertions){
		// 			right(value, assertions);
		// 		});
		// 	}
		// };
		// 
		// template <typename RightT>
		// BeNot<RightT> be_not(const RightT & right)
		// {
		// 	return {right};
		// }
		
		template <typename LeftT, typename RightT>
		struct BeAnd
		{
			const LeftT & left;
			const RightT & right;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				return left(value, assertions) && right(value, assertions);
			}
			
			friend std::ostream & operator<<(std::ostream & output, const BeAnd & condition)
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
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				return left(value, assertions) || right(value, assertions);
			}
			
			friend std::ostream & operator<<(std::ostream & output, const BeOr & condition)
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
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				// std::cerr << *this << ": " << (value == expected_value) << std::endl;
				return assertions.assert(value == expected_value, *this);
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
			
			friend std::ostream & operator<<(std::ostream & output, const BeEqual & condition)
			{
				return output << "be == " << Streams::safe(condition.expected_value);
			}
		};
		
		template <typename ExpectedValueT>
		struct BeNotEqual
		{
			const ExpectedValueT & expected_value;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				return assertions.assert(value != expected_value, *this);
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
			
			friend std::ostream & operator<<(std::ostream & output, const BeNotEqual & condition)
			{
				return output << "be != " << Streams::safe(condition.expected_value);
			}
		};
		
		template <typename ExpectedValueT>
		struct BeLessThan
		{
			const ExpectedValueT & expected_value;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				return assertions.assert(value < expected_value, *this);
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
			
			friend std::ostream & operator<<(std::ostream & output, const BeLessThan & condition)
			{
				return output << "be < " << Streams::safe(condition.expected_value);
			}
		};
		
		template <typename ExpectedValueT>
		struct BeLessThanOrEqual
		{
			const ExpectedValueT & expected_value;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				return assertions.assert(value <= expected_value, *this);
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
			
			friend std::ostream & operator<<(std::ostream & output, const BeLessThanOrEqual & condition)
			{
				return output << "be <= " << Streams::safe(condition.expected_value);
			}
		};
		
		template <typename ExpectedValueT>
		struct BeGreaterThan
		{
			const ExpectedValueT & expected_value;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				return assertions.assert(value > expected_value, *this);
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
			
			friend std::ostream & operator<<(std::ostream & output, const BeGreaterThan & condition)
			{
				return output << "be > " << Streams::safe(condition.expected_value);
			}
		};
		
		template <typename ExpectedValueT>
		struct BeGreaterThanOrEqual
		{
			const ExpectedValueT & expected_value;
			
			template <typename ValueT>
			bool operator()(const ValueT & value, Assertions & assertions) const
			{
				return assertions.assert(value >= expected_value, *this);
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
			
			friend std::ostream & operator<<(std::ostream & output, const BeGreaterThanOrEqual & condition)
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
}
