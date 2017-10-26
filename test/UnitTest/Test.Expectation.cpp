
#include <UnitTest/UnitTest.hpp>
#include <UnitTest/Expectation.hpp>

#include <stdexcept>

namespace UnitTest
{
	UnitTest::Suite ExpectationTestSuite {
		"UnitTest::Expectation",
		
		{"it should report expectations using to",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(10).to(be == 10);
				examiner.expect(10).to(be < 20);
				examiner.expect(10).to(be <= 20);
				
				// Expect 20 to be greater than 10
				// expect(20).to() > 10
				
				examiner.expect(20).to(be > 10);
				examiner.expect(20).to(be >= 10);
				examiner.expect(20).to(be != 10);
			}
		},
		
		{"it should report expectations using to_not",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(10).to_not(be == 20);
				examiner.expect(10).to_not(be > 20);
				examiner.expect(10).to_not(be >= 20);
				examiner.expect(20).to_not(be < 10);
				examiner.expect(20).to_not(be <= 10);
				examiner.expect(20).to_not(be != 20);
			}
		},
		
		{"it can use compound expectations",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(10).to(be > 0 && be < 20);
			}
		},
		
		{"it can expect exceptions",
			[](UnitTest::Examiner & examiner) {
				examiner.expect([]{
					throw std::runtime_error("error");
				}).to(throw_exception<std::exception>());
				
				examiner.expect([]{
					// throw std::runtime_error("error");
				}).to_not(throw_exception<std::exception>());
			}
		},
	};
}
