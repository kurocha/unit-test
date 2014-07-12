
#include <UnitTest/UnitTest.hpp>

namespace UnitTest
{
	UnitTest::Suite StatisticsTestSuite {
		"UnitTest::Statistics",
		
		{"Basic pass and fail",
			[](UnitTest::Examiner & examiner) {
				UnitTest::Statistics statistics;
				
				statistics.pass_test();
				statistics.fail_test();
				
				examiner.expect(statistics.passed()) == 1;
				examiner.expect(statistics.failed()) == 1;
				
				// Append statistics, in this case we just double everything:
				statistics += statistics;
				
				examiner.expect(statistics.passed()) == 2;
				examiner.expect(statistics.failed()) == 2;
			}
		},
	};

	UnitTest::Suite ExaminerTestSuite {
		"UnitTest::Examiner",

		{"Output messages and statistics",
			[](UnitTest::Examiner & examiner) {
				Statistics statistics;
				std::stringstream buffer;

				Examiner test_examiner(&statistics, buffer);
				
				test_examiner << "(A) This text should be displayed" << std::endl;
				test_examiner.check(false);
				
				test_examiner << "(B) This text should NOT be displayed" << std::endl;
				test_examiner.check(true);

				examiner << "The test examiner should have passed once." << std::endl;
				examiner.check_equal(statistics.passed(), 1);

				examiner << "The test examiner should have failed once." << std::endl;
				examiner.check_equal(statistics.failed(), 1);

				auto output_string = buffer.str();

				examiner << "The test examiner should have printed out the (A) message" << std::endl;
				examiner.check(output_string.find("(A)") != std::string::npos);

				examiner << "The test examiner shouldn't have printed out the (B) message" << std::endl;
				examiner.check(output_string.find("(B)") == std::string::npos);
			}
		},
	};
}
