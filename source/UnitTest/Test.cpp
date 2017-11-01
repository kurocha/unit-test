//
//  Test.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Test.hpp"

#include <Streams/Color.hpp>

namespace UnitTest
{
	static Streams::Color
		name_style(Streams::Color::WHITE, Streams::Color::UNSPECIFIED, Streams::Color::UNDERLINE),
		reset_style(-1, -1, Streams::Color::NORMAL);
	
	Test::Test(std::string name, TestFunctionT function) : _name(name), _function(function)
	{
	}
	
	void Test::operator()(Assertions & assertions) const noexcept
	{
		Examiner examiner{assertions};
		
		_function(examiner);
	}
	
	std::ostream & operator<<(std::ostream & output, const Test & test)
	{
		return output << name_style << Streams::safe(test.name()) << reset_style;
	}
}
