//
//  Suite.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Suite.hpp"

#include "Registry.hpp"

#include <Streams/Color.hpp>

namespace UnitTest
{
	static Streams::Color
		name_style(Streams::Color::WHITE, Streams::Color::UNSPECIFIED, Streams::Color::UNDERLINE),
		reset_style(-1, -1, Streams::Color::NORMAL);
	
	Suite::Suite(std::initializer_list<Entry> entries)
	{
		for (auto & entry : entries) {
			if (entry.test)
				_tests.emplace(_tests.end(), entry.name, entry.test);
			else
				_name = entry.name;
		}
		
		shared_registry()->add(this);
	}
	
	void Suite::operator()(Assertions & assertions)
	{
		for (auto test : _tests) {
			try {
				assertions.assert(test);
			} catch (...) {
				assertions.assert(false, "Test failed with unhandled exception");
			}
		}
	}
	
	std::ostream & operator<<(std::ostream & output, const Suite & suite)
	{
		return output << "Test Suite " << name_style << Streams::safe(suite.name()) << reset_style;
	}
}
