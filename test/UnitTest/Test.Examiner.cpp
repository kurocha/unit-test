//
//  Test.Examiner.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <UnitTest/Examiner.hpp>

namespace UnitTest
{
	UnitTest::Suite ExaminerTestSuite {
		"UnitTest::Examiner",

		{"it prints messages and statistics",
			[](UnitTest::Examiner & examiner) {
				Statistics statistics;
				std::stringstream buffer;

				Examiner test_examiner(&statistics, buffer);
				
				test_examiner << "(A) This text should be displayed" << std::endl;
				test_examiner.check(false);
				
				test_examiner << "(B) This text should NOT be displayed" << std::endl;
				test_examiner.check(true);

				examiner << "The test examiner should have passed once." << std::endl;
				examiner.expect(statistics.passed()).to(be == 1);

				examiner << "The test examiner should have failed once." << std::endl;
				examiner.expect(statistics.failed()).to(be == 1);

				auto output_string = buffer.str();

				examiner << "The test examiner should have printed out the (A) message" << std::endl;
				examiner.check(output_string.find("(A)") != std::string::npos);

				examiner << "The test examiner shouldn't have printed out the (B) message" << std::endl;
				examiner.check(output_string.find("(B)") == std::string::npos);
			}
		},
	};
}
