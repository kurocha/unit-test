//
//  Assertions.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 31/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <iostream>
#include <sstream>

#include <Streams/Terminal.hpp>
#include <Streams/Color.hpp>

namespace UnitTest
{
	class Assertions
	{
	public:
		// Top level constructor.
		Assertions(std::ostream & output, std::size_t level = 0, bool inverted = false) : _output(output), _level(level), _inverted(inverted)
		{
		}
		
		std::size_t passed() const noexcept {return _passed;}
		std::size_t failed() const noexcept {return _failed;}
		std::size_t total() const noexcept {return _passed + _failed;}
		
		std::ostream & output() const noexcept {return _output;}
		
		explicit operator bool() const noexcept
		{
			if (!_inverted) {
				return failed() == 0;
			} else {
				return failed() > 0 || passed() == 0;
			}
		}
		
		template <typename FunctionT>
		bool assert(FunctionT function)
		{
			std::stringstream buffer;
			Streams::TTY tty(buffer, _output);
			
			Assertions nested{buffer, _level+1, false};
			
			function(nested);
			
			_count += nested._count;
			
			return assert(!!nested, function, buffer);
		}
		
		template <typename FunctionT>
		bool refute(FunctionT function)
		{
			std::stringstream buffer;
			Assertions nested{buffer, _level+1, true};
			
			function(nested);
			
			_count += nested._count;
			
			return assert(!!nested, function, buffer);
		}
		
		friend std::ostream & operator<<(std::ostream & output, const Assertions & assertions);
		
		template <typename FunctionT>
		bool assert(bool condition, FunctionT function)
		{
			// std::cerr << "condition: " << condition << " inverted: " << _inverted << std::endl;
			
			if (condition) {
				_passed += 1;
				
				if (_inverted) {
					_output << indent() << function << std::endl;
				}
			} else {
				_failed += 1;
				
				if (!_inverted) {
					_output << indent() << function << std::endl;
				}
			}
			
			return condition;
		}
		
	private:
		template <typename FunctionT>
		bool assert(bool condition, FunctionT function, const std::stringstream & buffer)
		{
			_count += 1;
			
			if (condition) {
				_passed += 1;
				
				if (_inverted) {
					_output << indent() << function;
					
					if (buffer) {
						_output << " failed because all of the following passed:" << std::endl;
						_output << buffer.rdbuf() << std::endl;
					}
				}
			} else {
				_failed += 1;
				
				if (!_inverted) {
					_output << indent() << function;
					
					if (buffer) {
						//✓ ✗
						_output << " failed because all of the following failed:" << std::endl;
						_output << buffer.rdbuf() << std::endl;
					}
				}
			}
			
			return condition;
		}
		
		std::string indent() const
		{
			return std::string(_level, '\t');
		}
		
		std::ostream & _output;
		std::size_t _level = 0;
		bool _inverted = false;
		
		std::size_t _passed = 0, _failed = 0, _count = 0;
	};
}
