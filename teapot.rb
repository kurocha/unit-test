
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

required_version "0.8.0"

define_target "unit-test" do |target|
	target.build do |environment|
		build_directory(package.path, 'source', environment)
	end
	
	target.depends :platform
	target.depends "Language/C++11"
	
	target.provides "Library/UnitTest" do
		append linkflags "-lUnitTest"
	end
end

define_target "unit-test-tests" do |target|
	target.build do |environment|
		build_directory(package.path, 'test', environment)
	end
	
	target.run do |environment|
		environment = environment.flatten
		
		Commands.run(environment[:install_prefix] + "bin/unit-tests-test-runner")
	end
	
	target.depends :platform
	target.depends "Language/C++11"
	target.depends "Library/UnitTest"
	
	target.provides "Test/UnitTest"
end

define_configuration "travis" do |configuration|
	configuration[:source] = "https://github.com/dream-framework"
	
	configuration.require "platforms"
	
	configuration[:run] = ["Test/UnitTest"]
end
