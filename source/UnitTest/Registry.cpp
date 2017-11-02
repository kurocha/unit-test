//
//  Registry.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Registry.hpp"

#include "Format.hpp"

namespace UnitTest
{
	void Registry::add(Suite * suite) {
		_suites.push_back(suite);
	}
	
	Assertions Registry::perform_tests(const Names & names, bool verbose)
	{
		// Enable color output:
		Streams::TTY tty(std::cerr, Streams::terminal_type(std::cerr));
		Assertions overall(std::cerr);
		
		for (auto suite : _suites) {
			if (names.empty() || names.find(suite->name()) != names.end()) {
				overall.assert(*suite, verbose);
			}
		}
		
		std::cerr << overall << std::endl;
		
		return overall;
	}
	
	Registry * shared_registry() {
		static Registry * _shared_registry = nullptr;

		if (!_shared_registry)
			_shared_registry = new Registry;
		
		return _shared_registry;
	}
}
