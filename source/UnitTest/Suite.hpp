//
//  Suite.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Test.hpp"

#include <vector>

namespace UnitTest
{
	class Suite {
	public:
		struct Entry {
			const char * name;
			TestFunctionT test;
			
			Entry(const char * name_) : name(name_) {
			}
			
			Entry(const char * name_, TestFunctionT test_) : name(name_), test(test_) {
			}
		};
	
	protected:
		std::string _name;
		std::vector<Test> _tests;

	public:
		Suite(std::initializer_list<Entry> entries);
		
		Statistics run(std::ostream & out);
		
		auto & name() const {return _name;}
		auto & tests() const {return _tests;}
	};
}
