
#include <UnitTest/UnitTest.h>

UnitTest::Suite test_statistics_suite {
	"Test Statistics",
	
	{"Basic pass and fail working correctly",
		[](UnitTest::Examiner * examiner) {
			UnitTest::Statistics statistics;
			
			statistics.pass_test();
			statistics.fail_test();
			
			examiner->check_equal(statistics.failed(), 1);
		}
	},
};
