//
//  Format.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 2/11/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <Streams/Safe.hpp>
#include <Streams/Tuple.hpp>
#include <Streams/Container.hpp>

#include <Streams/Terminal.hpp>
#include <Streams/Color.hpp>

namespace UnitTest
{
	class Test;
	class Suite;
	
	namespace Format
	{
		extern const Streams::Color SUITE, TEST, VARIABLE, PASSED, FAILED, RESET;
		
		template <typename ValueT>
		auto variable(const ValueT & value)
		{
			return VARIABLE(Streams::safe(value));
		}
	}
}
