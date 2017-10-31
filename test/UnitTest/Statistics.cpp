//
//  Test.Statistics.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <UnitTest/Statistics.hpp>

namespace UnitTest
{
	using namespace UnitTest::Expectations;
	
	UnitTest::Suite StatisticsTestSuite {
		"UnitTest::Statistics",
		
		{"it can pass and fail tests",
			[](UnitTest::Examiner & examiner) {
				UnitTest::Statistics statistics;
				
				statistics.pass();
				statistics.fail();
				
				examiner.expect(statistics.passed()) == 1;
				examiner.expect(statistics.failed()) == 1;
				
				// Append statistics, in this case we just double everything:
				statistics += statistics;
				
				examiner.expect(statistics.passed()) == 2;
				examiner.expect(statistics.failed()) == 2;
			}
		},
	};
}
