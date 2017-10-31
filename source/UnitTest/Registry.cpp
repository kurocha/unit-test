//
//  Registry.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Registry.hpp"

#include <Streams/Terminal.hpp>

namespace UnitTest
{
	void Registry::add(Suite * suite) {
		_suites.push_back(suite);
	}
	
	Statistics Registry::perform_tests(Names filter)
	{
		// Enable color output:
		Streams::TTY tty(std::cerr, Streams::terminal_type(std::cerr));
		
		Assertions overall(std::cerr);
		
		for (auto suite : _suites) {
			if (filter.empty() || filter.find(suite->name()) != filter.end()) {
				overall.assert(suite);
			}
		}
		
		return overall;
	}
	
	Registry * shared_registry() {
		static Registry * _shared_registry = nullptr;

		if (!_shared_registry)
			_shared_registry = new Registry;
		
		return _shared_registry;
	}
}
