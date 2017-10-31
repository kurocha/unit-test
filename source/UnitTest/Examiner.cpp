//
//  Examiner.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Examiner.hpp"

#include <Streams/Color.hpp>

namespace UnitTest
{
	static Streams::Color
		failed_style(Streams::Color::RED),
		reset_style(-1, -1, Streams::Color::NORMAL);
	
	Examiner::Examiner(Assertions & assertions, std::ostream & output) : _assertions(assertions), _output(output)
	{
	}
	
	void Examiner::check(bool condition) {
		if (condition == false) {
			fail() << _buffer.rdbuf();
		} else {
			pass();
		}

		// Clear the buffer:
		_buffer.str("");
	}
	
	std::ostream & Examiner::fail()
	{
		_statistics->fail();
		
		return _output << failed_style << "Failed check: " << reset_style;
	}
	
	void Examiner::pass()
	{
		_statistics->pass();
	}
}
