//
//  Test.Statistics.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <UnitTest/Assertions.hpp>

namespace UnitTest
{
	using namespace UnitTest::Expectations;
	
	UnitTest::Suite AssertionsTestSuite {
		"UnitTest::Assertions",
		
		{"it can pass and fail tests",
			[](UnitTest::Examiner & examiner) {
				std::stringstream buffer;
				UnitTest::Assertions assertions(buffer);
				
				assertions.assert(true, "It passed.");
				assertions.assert(false, "It failed.");
				
				examiner.expect(assertions.passed()).to(be == 1);
				examiner.expect(assertions.failed()).to(be == 1);
				
				examiner.expect(buffer.str()).to(include("It failed."));
			}
		},
		
		{"it prints messages",
			[](UnitTest::Examiner & examiner) {
				std::stringstream buffer;
				Assertions assertions(buffer);

				assertions.assert(false, "(A) This text should be displayed.");
				assertions.assert(true, "(B) This text shold be displayed.");

				// examiner << "The test examiner should have passed once." << std::endl;
				examiner.expect(assertions.passed()) == 1;

				// examiner << "The test examiner should have failed once." << std::endl;
				examiner.expect(assertions.failed()) == 1;

				auto output_string = buffer.str();

				// examiner << "The test examiner should have printed out the (A) message" << std::endl;
				examiner.expect(output_string).to(include("(A)"));

				// examiner << "The test examiner shouldn't have printed out the (B) message" << std::endl;
				examiner.expect(output_string).to_not(include("(B)"));
			}
		},
	};
}
