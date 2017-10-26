//
//  Test.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Test.hpp"

namespace UnitTest
{
	Test::Test(std::string name, TestFunctionT function) : _name(name), _function(function) {
	}

	void Test::invoke(Examiner & examiner) {
		_function(examiner);
	}
}
