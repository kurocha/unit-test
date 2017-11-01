//
//  Registry.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Suite.hpp"

#include <set>

namespace UnitTest
{
	typedef std::set<std::string> Names;
	
	/// A class that collects all defined unit tests.
	class Registry {
		std::vector<Suite *> _suites;
		
	public:
		void add(Suite * suite);
		
		// If tests is not empty, it will be used to limit tests to 
		Assertions perform_tests(Names names);
	};
	
	/// The global registry object.
	Registry * shared_registry();
}
