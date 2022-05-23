//
//  Assert.hpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 24/05/2022.
//  Copyright, 2022, by Samuel Williams. All rights reserved.
//

#pragma once

#include <stdexcept>

// Disable assert() macro. You should not be using this in test code.
#include <assert.h>
#undef assert

inline void assert(bool expression) {
	if (!expression) {
		throw std::runtime_error("assertion failed");
	}
}
