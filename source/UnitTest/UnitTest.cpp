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

#include <Streams/Terminal.hpp>
#include <Streams/Color.hpp>

namespace UnitTest {
	const char * VERSION = "1.0.0";
	
	Streams::Color
		passed_style(Streams::Color::GREEN, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		failed_style(Streams::Color::RED, Streams::Color::UNSPECIFIED, Streams::Color::BOLD),
		reset_style(-1, -1, Streams::Color::NORMAL);
	
	namespace Options {
		std::string failure_command;
	}
	
	Statistics::Statistics () : _failed(0), _passed(0)
	{
	}

	void Statistics::fail_test ()
	{
		_failed += 1;
	}

	void Statistics::pass_test ()
	{
		_passed += 1;
	}

	void Statistics::operator+= (const Statistics & other)
	{
		_passed += other._passed;
		_failed += other._failed;
	}

	void Statistics::print_summary (std::string name, std::ostream & output) const
	{
		output << "[" << name << "] " << passed_style << _passed << " passed" << reset_style;
		
		if (_failed > 0)
			output << failed_style << " " << _failed << " failed" << reset_style;

		output << " out of " << _failed + _passed << " total" << std::endl;
	}
	
	Examiner::Examiner(Statistics * statistics, std::ostream & output) : _statistics(statistics), _output(output)
	{
	}
	
	/// This function is typically used for parsing OpenGL extension strings.
	template <typename OutT>
	void split(const std::string & input, const char divider, OutT result) {
		std::size_t pos = 0, next = 0;

		do {
			next = input.find(divider, pos);

			std::string bit(&input[pos], (next == std::string::npos) ? (input.size() - pos) : (next - pos));
			*result++ = bit;

			pos = next + 1;
		} while (next != std::string::npos);
	}
	
	static void run(const std::string & command) {
		pid_t child = fork();

		if (child) {
			waitpid(child, NULL, 0);
		} else {
			std::vector<std::string> arguments;
			split(command, ' ', std::back_inserter(arguments));

			std::vector<const char *> argv;
			for (auto & argument : arguments)
				argv.push_back(argument.c_str());

			argv.push_back(nullptr);

			dup2(2, 1);
			execv(argv[0], (char *const *)argv.data());
			abort();
		}
	}
	
	void Examiner::check(bool condition) {
		if (condition == false) {
			_statistics->fail_test();

			if (Options::failure_command.size() > 0) {
				run(Options::failure_command);
			}

			_output << failed_style << "Failed check: " << reset_style << _buffer.rdbuf();
		} else {
			_statistics->pass_test();
		}

		// Clear the buffer:
		_buffer.str("");
	}

	Test::Test(std::string name, TestFunctionT function) : _name(name), _function(function) {
	}

	void Test::invoke(Examiner & examiner) {
		_function(examiner);
	}
	
	Suite::Suite(std::initializer_list<Entry> entries) {
		for (auto & entry : entries) {
			if (entry.test)
				_tests.emplace(_tests.end(), entry.name, entry.test);
			else
				_name = entry.name;
		}
		
		shared_registry()->add(this);
	}
	
	Statistics Suite::run(std::ostream & out) {
		Statistics total;
		
		out << "--- " << _name << " ---" << std::endl;
		
		for (auto test : _tests) {
			Statistics results;
			Examiner examiner(&results);
			
			try {
				test.invoke(examiner);
			} catch (std::exception & error) {
				out << "Test failed with unhandled exception: " << error.what() << std::endl;
				results.fail_test();
			}
			
			results.print_summary(test.name(), out);
			
			total += results;
		}
		
		return total;
	}
	
	void Registry::add(Suite * suite) {
		_suites.push_back(suite);
	}
	
	Statistics Registry::perform_tests(Names filter)
	{
		// Enable color output:
		Streams::TTY tty(std::cerr, Streams::terminal_type(std::cerr));
		
		std::cerr << "Colors: " << (bool)tty << std::endl;
		
		Statistics overall;
		
		for (auto suite : _suites) {
			if (filter.empty() || filter.find(suite->name()) != filter.end()) {
				std::cerr << std::endl;
				overall += suite->run(std::cerr);
			}
		}
		
		std::cerr << std::endl;
		overall.print_summary("Summary", std::cerr);
		
		return overall;
	}
	
	Registry * shared_registry() {
		static Registry * _shared_registry = nullptr;

		if (!_shared_registry)
			_shared_registry = new Registry;
		
		return _shared_registry;
	}
	
	static void segmentation_fault(int) {
		std::cerr << "*** Segmentation Fault ***" << std::endl;
		run(Options::failure_command);
		exit(-1);
	}
}

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
	
	for (int i = 1; i < argc; i += 1) {
		auto arg = std::string(argv[i]);
		
		if (arg == "--on-failure" && (i+1) < argc) {
			// Get the absolute path to the failure command:
			char * resolved_name = realpath(argv[i+1], NULL);
			UnitTest::Options::failure_command = std::string(resolved_name);
			free(resolved_name);
		}
		
		else if (arg == "--help") {
			std::cerr << "Usage: " << argv[0] << " [options]" << std::endl;
			std::cerr << "This script can be used to run a set of compiled unit tests." << std::endl;
			std::cerr << std::endl;
			std::cerr << "	--on-failure [script-path]" << std::endl;
			std::cerr << "		Execute the given script when a unit test fails via fork-exec." << std::endl;
			
			return 0;
		}
		
		else {
			filter.insert(arg);
		}
	}
	
	// Change the working directory so that unit tests can expect some consistency if/when loading external resources:
	change_directory(argv[0]);
	
	if (UnitTest::Options::failure_command.size() > 0) {
		signal(SIGSEGV, UnitTest::segmentation_fault);
	}
	
	UnitTest::Statistics statistics = UnitTest::shared_registry()->perform_tests(filter);
	
	if (statistics.failed()) {
		return 1;
	} else {
		return 0;
	}
}
