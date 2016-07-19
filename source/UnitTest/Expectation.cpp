//
//  Expectation.cpp
//  This file is part of the "Unit Test" project and released under the MIT License.
//
//  Created by Samuel Williams on 12/7/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include "Expectation.hpp"

namespace UnitTest
{
	std::ostream & operator<< (std::ostream & out, const std::type_info & rhs)
	{
		return out << "typeinfo(" << rhs.name() << ")";
	}
	
	std::ostream & operator<< (std::ostream & out, const std::nullptr_t &)
	{
		return out << "nullptr";
	}
}
