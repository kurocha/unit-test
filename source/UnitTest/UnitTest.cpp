//
//  UnitTest/UnitTest.cpp
//  This file is part of the "UnitTest" project, and is released under the MIT license.
//
//  Created by Samuel Williams on 25/09/06.
//  Copyright 2006 Samuel Williams. All rights reserved.
//

#include "UnitTest.hpp"
#include <iostream>

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include <system_error>
#include <errno.h>

static void change_directory(std::string file_path)
{
	auto last_slash = file_path.find_last_of('/');
	
	if (last_slash == std::string::npos)
		return;
	
	file_path.resize(last_slash);
	
	auto result = chdir(file_path.c_str());
	
	if (result == -1)
		throw std::system_error(errno, std::generic_category(), "chdir");
}

int main (int argc, char** argv)
{
	UnitTest::Names filter;
	bool verbose = true;
	
	for (int i = 1; i < argc; i += 1) {
		if (std::string(argv[i]) == "--quiet") {
			verbose = false;
		} else {
			filter.insert(argv[i]);
		}
	}
	
	// Change the working directory so that unit tests can expect some consistency if/when loading external resources:
	change_directory(argv[0]);
	
	// if (UnitTest::Options::failure_command.size() > 0) {
	// 	signal(SIGSEGV, UnitTest::segmentation_fault);
	// }
	
	auto results = UnitTest::shared_registry()->perform_tests(filter, verbose);
	
	if (!results) {
		return 1;
	} else {
		return 0;
	}
}
