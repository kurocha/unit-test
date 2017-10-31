//
//  Assertions.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 31/10/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Assertions.hpp"

namespace UnitTest
{
	static Streams::Color
		passed_style(Streams::Color::GREEN, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		failed_style(Streams::Color::RED, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		reset_style(-1, -1, Streams::Color::NORMAL);
	
	Assertions::Assertions(std::ostream & output, std::size_t level) : _output(output), _level(level)
	{
	}
	
	std::ostream & Assertions::assert(bool condition) noexcept
	{
		if (condition) {
			_passed += 1;
		} else {
			_failed += 1;
		}
		
		auto & assertion = _ordered.emplace_back(condition)
		
		return assertion.buffer;
	}

	void Assertions::operator+=(const Assertions & other)
	{
		_passed += other._passed;
		_failed += other._failed;
		
		_ordered.insert(_ordered.end(), other._ordered.begin(), other._ordered.end());
	}
	
	std::ostream & operator<<(std::ostream & output, const Assertions & assertions)
	{
		output << passed_style << _passed << " passed" << reset_style;
		
		if (_failed > 0)
			output << failed_style << " " << _failed << " failed" << reset_style;
		
		output << " out of " << _failed + _passed << " total" << std::endl;
	}
}
