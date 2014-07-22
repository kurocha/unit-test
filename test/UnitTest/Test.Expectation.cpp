
#include <UnitTest/UnitTest.hpp>
#include <UnitTest/Expectation.hpp>

namespace UnitTest
{
	UnitTest::Suite ExpectationTestSuite {
		"UnitTest::Expectation",
		
		{"it should report expectations",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(10) == 10;
				examiner.expect(10) < 20;
				examiner.expect(10) <= 20;
				examiner.expect(20) > 10;
				examiner.expect(20) >= 10;
				examiner.expect(20) != 10;
			}
		},
	};
}
