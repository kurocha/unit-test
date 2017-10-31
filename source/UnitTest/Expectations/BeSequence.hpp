//
//  BeSequence.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <utility>
#include <array>

namespace UnitTest
{
	namespace Expectations
	{
		template <typename HeadT, std::size_t N>
		struct BeSequence
		{
			const HeadT sequence[N];
			
			struct Offset
			{
				std::size_t index;
				const HeadT & value;
				
				friend std::ostream & operator<<(std::ostream & output, const Offset & offset)
				{
					return output << "have value " << Streams::safe(offset.value) << " at index " << offset.index;
				}
			};
			
			struct OutOfBounds
			{
				std::size_t index;
				std::size_t size;
				
				friend std::ostream & operator<<(std::ostream & output, const OutOfBounds & out_of_bounds)
				{
					return output << "have " << out_of_bounds.size << " items but got " << out_of_bounds.index;
				}
			};
			
			template <typename ValueT>
			void operator()(To<ValueT> & to)
			{
				std::size_t i = 0;
				
				for (const auto & item : to.value) {
					if (!to.check(i < N, OutOfBounds{i, N})) {
						break;
					}
					
					to.check(item == sequence[i], Offset{i, item});
					
					i++;
				}
				
				to.check(i == N, OutOfBounds{i, N});
			}
			
			friend std::ostream & operator<<(std::ostream & output, const BeSequence & condition)
			{
				return output << "be sequence " << Streams::safe(condition.sequence);
			}
		};
		
		template <typename ...Types>
		constexpr auto sequence(Types&&... values)
		{
			return std::array<typename std::decay<typename std::common_type<Types...>::type>::type, sizeof...(Types)>{{std::forward<Types>(values)...}};
		}
		
		template <typename ...Types>
		constexpr auto be_sequence(Types&&... values)
		{
			return BeSequence<typename std::decay<typename std::common_type<Types...>::type>::type, sizeof...(Types)>{{std::forward<Types>(values)...}};
		}
	}
}
