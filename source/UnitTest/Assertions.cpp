//
//  Assertions.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 31/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Assertions.hpp"

#include <Streams/Color.hpp>

namespace UnitTest
{
	Assertions::Assertions(std::ostream & output, std::size_t level, bool inverted) : _output(output), _level(level), _inverted(inverted)
	{
	}
	
	Assertions::operator bool() const noexcept
	{
		if (!_inverted) {
			return failed() == 0;
		} else {
			return failed() > 0 || passed() == 0;
		}
	}
	
	std::ostream & operator<<(std::ostream & output, const Assertions & assertions)
	{
		output << Format::PASSED << assertions.passed() << " passed" << Streams::Color();
		
		if (assertions.failed())
			output << Format::FAILED << " " << assertions.failed() << " failed" << Streams::Color();
		
		output << " out of " << assertions.total() << " total (" << assertions._count << " assertions)";
		
		return output;
	}
}
