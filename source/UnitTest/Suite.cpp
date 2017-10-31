//
//  Suite.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Suite.hpp"

#include "Registry.hpp"

namespace UnitTest
{
	Suite::Suite(std::initializer_list<Entry> entries)
	{
		for (auto & entry : entries) {
			if (entry.test)
				_tests.emplace(_tests.end(), entry.name, entry.test);
			else
				_name = entry.name;
		}
		
		shared_registry()->add(this);
	}
	
	void Suite::operator()(Assertions & assertions)
	{
		for (auto test : _tests) {
			try {
				assertions.assert(test);
			} catch (std::exception & error) {
				assertions.assert(false, )
				
				out << "Test failed with unhandled exception: " << error.what() << std::endl;
				results.fail();
			}
			
			out << test.name() << ": " << results << std::endl;
			
			total += results;
		}
		
		return total;
	}
	
	std::ostream & operator<<(std::ostream & output, const Suite & suite)
	{
		return output << "--- " << suite.name() << " ---";
	}
}
