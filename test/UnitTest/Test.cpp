//
//  Test.Test.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <UnitTest/Test.hpp>

namespace UnitTest
{
	using namespace UnitTest::Expectations;
	
	UnitTest::Suite TestTestSuite {
		"UnitTest::Test",
		
		{"it has a name",
			[](UnitTest::Examiner & examiner) {
				Test test = {"Foobar", [](UnitTest::Examiner & examiner){}};
				
				examiner.expect(test.name()).to(be == std::string{"Foobar"});
			}
		},
	};
}
