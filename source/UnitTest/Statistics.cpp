//
//  Statistics.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Statistics.hpp"

#include <iostream>

#include <Streams/Color.hpp>

namespace UnitTest
{
	static Streams::Color
		passed_style(Streams::Color::GREEN, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		failed_style(Streams::Color::RED, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		reset_style(-1, -1, Streams::Color::NORMAL);
	
	Statistics::Statistics () : _failed(0), _passed(0)
	{
	}

	void Statistics::fail_test ()
	{
		_failed += 1;
	}

	void Statistics::pass_test ()
	{
		_passed += 1;
	}

	void Statistics::operator+= (const Statistics & other)
	{
		_passed += other._passed;
		_failed += other._failed;
	}

	void Statistics::print_summary (std::string name, std::ostream & output) const
	{
		output << "[" << name << "] " << passed_style << _passed << " passed" << reset_style;
		
		if (_failed > 0)
			output << failed_style << " " << _failed << " failed" << reset_style;

		output << " out of " << _failed + _passed << " total" << std::endl;
	}
}
