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
		// Top level constructor.
		Assertions(std::ostream & output, std::size_t level = 0);
		
		std::size_t passed() const noexcept {return _passed;}
		std::size_t failed() const noexcept {return _failed;}
		
		template <typename FunctionT>
		bool assert(FunctionT function)
		{
			std::stringstream _buffer;
			Assertions nested{_buffer, _level+1};
			
			function(nested);
			
			if (nested.failed() == 0) {
				_passed += 1;
				
				return true;
			} else {
				_failed += 1;
				
				_output << std::string("\t", _level) << function << std::endl;
				_output << _buffer.rdbuf();
				
				return false;
			}
		}
		
		template <typename FunctionT>
		bool refute(FunctionT function)
		{
			std::stringstream _buffer;
			Assertions nested{_buffer, _level+1};
			
			function(nested);
			
			if (nested.failed() > 0 || nested.passed() == 0) {
				_passed += 1;
				
				return true;
			} else {
				_failed += 1;
				
				_output << std::string("\t", _level) << function << std::endl;
				_output << _buffer.rdbuf();
				
				return false;
			}
		}
		
		bool assert(bool condition)
		{
			if (condition) {
				_passed += 1;
			} else {
				_failed += 1;
				
				_output << std::string("\t", _level) << function << std::endl;
			}
		}
		
		friend std::ostream & operator<<(std::ostream & output, const Assertions & assertions);
		
	private:
		std::ostream & _output;
		std::size_t _level = 0;
		
		std::size_t _passed = 0, _failed = 0;
	};
}
