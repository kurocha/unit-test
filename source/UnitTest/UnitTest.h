//
//  Core/CodeTest.h
//  This file is part of the "Dream" project, and is released under the MIT license.
//
//  Created by Samuel Williams on 14/09/06.
//  Copyright 2006 Samuel WilliamsWilliams. All rights reserved.
//
//

#ifndef _UNIT_TEST_H
#define _UNIT_TEST_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>

namespace UnitTest {
	/// Keep track of statistics.
	class Statistics {
		std::size_t _failed;
		std::size_t _passed;

	public:
		Statistics ();

		std::size_t passed() const { return _passed; }
		std::size_t failed() const { return _failed; }

		void fail_test ();
		void pass_test ();

		void print_summary (std::string name, std::ostream & out) const;

		void operator+= (const Statistics & other);
	};

	/// A examiner runs the tests and keeps track of the results.
	class Examiner {
		Statistics * _statistics;

		std::stringstream _buffer;
		std::ostream & _output;

	public:
		Examiner(Statistics * statistics, std::ostream & output = std::cerr);
		
		void check(bool condition);
		
		template <typename LeftT, typename RightT>
		void check_equal(LeftT left, RightT right) {
			(*this) << left << " == " << right << std::endl;
			
			check(left == right);
		}

		template <typename ValueT>
		std::ostream & operator<< (ValueT && value)
		{
			return (_buffer << value);
		}
	};

	// The test function type:
	typedef std::function<void (Examiner &)> TestFunctionT;

	/// A test that must be completed successfully.
	class Test {
		std::string _name;
		TestFunctionT _function;
		
	public:
		Test(std::string name, TestFunctionT function);
		
		std::string name() const { return _name; }
		
		void invoke(Examiner & examiner);
	};
	
	std::ostream & operator<< (std::ostream & out, const std::type_info & rhs);
	
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
		std::vector<Test *> _tests;

	public:
		Suite(std::initializer_list<Entry> entries);

		Statistics run(std::ostream & out);
	};
	
	/// A class that collects all defined unit tests.
	class Registry {
		std::vector<Suite *> _suites;
		
	public:
		void add(Suite * suite);
		Statistics perform_tests();
	};
	
	/// The global registry object.
	Registry * shared_registry();
}

#endif
