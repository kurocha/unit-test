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
	static Streams::Color
		passed_style(Streams::Color::GREEN, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		failed_style(Streams::Color::RED, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		reset_style(-1, -1, Streams::Color::NORMAL);
	
	std::ostream & operator<<(std::ostream & output, const Assertions & assertions)
	{
		output << passed_style << assertions.passed() << " passed" << reset_style;
		
		if (assertions.failed())
			output << failed_style << " " << assertions.failed() << " failed" << reset_style;
		
		output << " out of " << assertions.total() << " total (" << assertions._count << " assertions)";
		
		return output;
	}
}
