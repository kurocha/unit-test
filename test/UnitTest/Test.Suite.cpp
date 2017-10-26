//
//  Test.Suite.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <UnitTest/Suite.hpp>

namespace UnitTest
{
	UnitTest::Suite SuiteTestSuite {
		"UnitTest::Suite",
		
		{"it has a name",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(SuiteTestSuite.name()).to(be == "UnitTest::Suite");
			}
		},
		
		{"it has some tests",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(SuiteTestSuite.tests().size()).to(be > 0);
			}
		},
	};
}
