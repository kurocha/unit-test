//
//  Statistics.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <cstddef>
#include <iosfwd>

namespace UnitTest
{
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
}
