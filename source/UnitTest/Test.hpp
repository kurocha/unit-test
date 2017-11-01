//
//  Test.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 27/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Examiner.hpp"

#include <functional>

namespace UnitTest
{
	// The test function type:
	typedef std::function<void (Examiner &)> TestFunctionT;

	/// A test that must be completed successfully.
	class Test
	{
		std::string _name;
		TestFunctionT _function;
		
	public:
		Test(std::string name, TestFunctionT function);
		
		std::string name() const {return _name;}
		
		void operator()(Assertions & assertions) const noexcept;
		
		friend std::ostream & operator<<(std::ostream & output, const Test & test);
	};
}
