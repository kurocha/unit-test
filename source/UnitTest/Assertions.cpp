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
	const Streams::Color
		PASSED_STYLE(Streams::Color::GREEN, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		FAILED_STYLE(Streams::Color::RED, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		RESET_STYLE(-1, -1, Streams::Color::NORMAL);
	
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
		output << PASSED_STYLE << assertions.passed() << " passed" << RESET_STYLE;
		
		if (assertions.failed())
			output << FAILED_STYLE << " " << assertions.failed() << " failed" << RESET_STYLE;
		
		output << " out of " << assertions.total() << " total (" << assertions._count << " assertions)";
		
		return output;
	}
}
