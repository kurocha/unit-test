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

#include "Format.hpp"

namespace UnitTest
{
	class Assertions
	{
		std::string indent() const
		{
			return std::string(_level, '\t');
		}
		
		auto pass_prefix() const
		{
			return Format::PASSED("✓ ");
		}
		
		auto fail_prefix() const
		{
			return Format::FAILED("✗ ");
		}
		
	public:
		Assertions(std::ostream & output, std::size_t level = 0, bool inverted = false);
		
		std::size_t passed() const noexcept {return _passed;}
		std::size_t failed() const noexcept {return _failed;}
		std::size_t total() const noexcept {return _passed + _failed;}
		
		std::ostream & output() const noexcept {return _output;}
		
		explicit operator bool() const noexcept;
		
		template <typename FunctionT>
		bool assert(FunctionT && function, bool verbose = false)
		{
			std::stringstream buffer;
			Streams::TTY tty(buffer, _output);
			Assertions nested{buffer, _level+1, false};
			
			function(nested);
			
			_count += nested._count;
			
			return assert(nested, function, buffer, verbose);
		}
		
		template <typename FunctionT>
		bool refute(FunctionT && function, bool verbose = false)
		{
			std::stringstream buffer;
			Streams::TTY tty(buffer, _output);
			Assertions nested{buffer, _level+1, true};
			
			function(nested);
			
			_count += nested._count;
			
			return assert(nested, function, buffer, verbose);
		}
		
		friend std::ostream & operator<<(std::ostream & output, const Assertions & assertions);
		
		template <typename FunctionT>
		bool assert(bool condition, FunctionT && function)
		{
			if (condition) {
				_passed += 1;
				
				if (_inverted) {
					_output << indent() << pass_prefix() << function << std::endl;
				}
			} else {
				_failed += 1;
				
				if (!_inverted) {
					_output << indent() << fail_prefix() << function << std::endl;
				}
			}
			
			return condition;
		}
		
	private:
		template <typename FunctionT>
		bool assert(Assertions & nested, FunctionT & function, const std::stringstream & buffer, bool verbose)
		{
			_count += 1;
			
			if (nested) {
				_passed += 1;
				
				if (_inverted) {
					_output << indent() << fail_prefix() << function;
					
					if (verbose)
						_output << ": " << nested << std::endl;
					else
						_output << std::endl;
					
					if (buffer) {
						_output << buffer.rdbuf();
					}
				} else if (verbose) {
					_output << indent() << pass_prefix() << function << ": " << nested << std::endl;
					
					if (buffer) _output << buffer.str();
				}
				
				return true;
			} else {
				_failed += 1;
				
				if (!_inverted) {
					_output << indent() << fail_prefix() << function;
					
					if (verbose)
						_output << ": " << nested << std::endl;
					else
						_output << std::endl;
					
					if (buffer) {
						_output << buffer.rdbuf();
					}
				} else if (verbose) {
					_output << indent() << pass_prefix() << function << ": " << nested << std::endl;
					
					if (buffer) _output << buffer.str();
				}
				
				return false;
			}
		}
		
		std::ostream & _output;
		std::size_t _level = 0;
		bool _inverted = false;
		
		std::size_t _passed = 0, _failed = 0, _count = 0;
	};
}
