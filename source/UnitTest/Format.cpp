//
//  Format.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 2/11/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Format.hpp"

#include "Test.hpp"
#include "Suite.hpp"

namespace UnitTest
{
	namespace Format
	{
		const Streams::Color
			SUITE(Streams::Color::YELLOW, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
			TEST(Streams::Color::YELLOW, Streams::Color::UNSPECIFIED, Streams::Color::NORMAL),
			VARIABLE(Streams::Color::CYAN, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
			PASSED(Streams::Color::GREEN, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
			FAILED(Streams::Color::RED, Streams::Color::UNSPECIFIED, Streams::Color::BOLD);
	}
}
