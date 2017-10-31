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
	
	Statistics Suite::run(std::ostream & out)
	{
		Statistics total;
		
		out << *this << std::endl;
		
		for (auto test : _tests) {
			Statistics results;
			Examiner examiner(&results);
			
			try {
				test.invoke(examiner);
			} catch (std::exception & error) {
				out << "Test failed with unhandled exception: " << error.what() << std::endl;
				results.fail();
			}
			
			results.print_summary(test.name(), out);
			
			total += results;
		}
		
		return total;
	}
	
	std::ostream & operator<<(std::ostream & output, const Suite & suite)
	{
		return output << "--- " << suite.name() << " ---";
	}
}
