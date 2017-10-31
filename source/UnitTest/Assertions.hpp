//
//  Assertions.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 31/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace UnitTest
{
	class Assertions
	{
	public:
		Assertions(std::ostream & output = std::cerr);
		Assertions(Assertions * parent, bool expected = true);
		~Assertions();
		
		std::size_t passed() const noexcept {return _passed;}
		std::size_t failed() const noexcept {return _failed;}

		std::ostream & assert(bool condition);

		explicit operator bool() const noexcept
		{
			return failed() == 0;
		}
		
		friend std::ostream & operator<<(std::ostream & output, const Assertions & assertions);
		
	private:
		std::ostream & _output;
		Assertions * _parent = nullptr;
		
		// Whether we are expecting all assertions to pass or at least one to fail.
		bool _expected = true;
		
		std::vector<Assertion> _ordered;
		std::size_t _passed = 0, _failed = 0;
	};
}
