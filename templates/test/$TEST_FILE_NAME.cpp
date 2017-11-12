//
//  $TEST_FILE_NAME.cpp
//  This file is part of the "$PROJECT_NAME" project and released under the $LICENSE.
//
//  Created by $AUTHOR_NAME on $DATE.
//  Copyright, $YEAR, by $AUTHOR_NAME. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <$TEST_SOURCE_HEADER>

<NAMESPACE>
using namespace UnitTest::Expectations;

UnitTest::Suite $TEST_SUITE_NAME {
	"$TEST_SUITE_DESCRIPTION",
	
	{"it should have some real tests",
		[](UnitTest::Examiner & examiner) {
			examiner.expect(false).to(be_true);
		}
	},
};
</NAMESPACE>
