
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

required_version "1.0"

define_target "unit-test" do |target|
	target.build do
		source_root = target.package.path + 'source'
		
		copy source: Files::Glob.new(source_root, "bin/**/*"), prefix: environment[:install_prefix]
		copy headers: Files::Glob.new(source_root, 'UnitTest/**/*.{h,hpp}'), prefix: environment[:install_prefix]
		
		build static_library: "UnitTest", 
			prefix: environment[:install_prefix], 
			source_files: Files::Glob.new(source_root, 'UnitTest/**/*.cpp')
	end
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.depends :platform
	target.depends "Language/C++11"
	
	target.provides "Library/UnitTest" do
		append linkflags "-lUnitTest"
	end
	
	target.provides "Rulebook/UnitTests" do
		rule "run.unit-tests" do
			input :test_runner
			
			apply do |arguments|
				run!(arguments[:test_runner])
			end
		end
	end
end

define_target "unit-test-tests" do |target|
	target.build do
		source_root = target.package.path + 'test'
		
		build executable: "UnitTest-tests", 
			prefix: environment[:install_prefix],
			source_files: Files::Glob.new(source_root, 'UnitTest/**/*.cpp')
		
		run executable: "UnitTest-tests",
			prefix: environment[:install_prefix]
	end
	
	target.depends "Build/Clang"
	
	target.depends :platform
	target.depends "Language/C++11"
	target.depends "Library/UnitTest"
	
	target.provides "Test/UnitTest"
end

define_configuration "travis" do |configuration|
	configuration[:source] = "https://github.com/dream-framework"
	
	configuration.require "platforms"
	
	configuration.require "build-files"
	
	configuration[:run] = ["Test/UnitTest"]
end

define_configuration "local" do |configuration|
	configuration[:source] = "../"
	
	configuration.require "platforms"
	
	configuration[:run] = ["Test/UnitTest"]
end

