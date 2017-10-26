//
//  Test.Registry.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <UnitTest/Registry.hpp>

namespace UnitTest
{
	UnitTest::Suite RegistryTestSuite {
		"UnitTest::Registry",
		
		{"it should have some real tests",
			[](UnitTest::Examiner & examiner) {
				examiner.expect(1).to(be_true);
			}
		},
	};
}
