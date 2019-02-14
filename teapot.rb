
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "2.3"

# Project Metadata

define_project "unit-test" do |project|
	project.title = "Unit Test"
	project.summary = 'A simple framework for C++ unit tests.'
	
	project.license = "MIT License"
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = "0.1.0"
end

# Build Targets

define_target 'unit-test-library' do |target|
	source_root = target.package.path + 'source'
	bin_root = target.package.path + 'bin'
	
	target.build do
		build prefix: target.name, static_library: 'UnitTest', source_files: source_root.glob('UnitTest/**/*.cpp')
	end
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.depends "Library/Streams"
	
	target.depends :platform
	target.depends "Language/C++14", private: true
	
	target.provides "Library/UnitTest" do
		append linkflags [
			->{build_prefix + target.name + 'UnitTest.a'},
		]
		
		append header_search_paths [
			source_root
		]
		
		define Rule, "copy.unit-tests" do
			input :test_assets
			
			parameter :prefix, optional: true do |path, arguments|
				arguments[:prefix] = environment[:build_prefix] + path
			end
			
			apply do |parameters|
				copy source: parameters[:test_assets], prefix: parameters[:prefix]
			end
		end
		
		define Rule, "run.unit-tests" do
			input :source_files
			
			parameter :prefix
			parameter :arguments
			
			parameter :executable_file, implicit: true do |arguments|
				environment[:install_prefix] + arguments[:prefix] + "bin/tests"
			end
			
			apply do |parameters|
				build prefix: parameters[:prefix],
					executable: "tests",
					executable_file: parameters[:executable_file],
					source_files: parameters[:source_files]
				
				run prefix: parameters[:prefix],
					executable: "tests",
					executable_file: parameters[:executable_file],
					arguments: parameters[:arguments]
			end
		end
	end
end

define_target "unit-test-tests" do |target|
	target.build do |*arguments|
		run prefix: target.name, source_files: target.package.path.glob("test/UnitTest/**/*.cpp"), arguments: arguments
	end
	
	target.depends 'Library/UnitTest'
	target.provides 'Test/UnitTest'
	
	target.depends 'Build/Files'
	target.depends "Build/Clang"
	
	target.depends :platform
	target.depends "Language/C++14", private: true
	
	target.provides "Test/UnitTest"
end

define_target "generate-unit-test" do |target|
	target.description = <<-EOF
		Generates a basic test file in the project.
	EOF
	
	target.depends "Generate/Template"
	target.provides "Generate/Unit/Test"
	
	def target.scope_for_namespace(namespace)
		open = namespace.collect{|name| "namespace #{name}\n{\n"}
		close = namespace.collect{ "}\n" }
	
		return open + close
	end
	
	target.build do |full_class_name|
		*path, class_name = full_class_name.split(/::/)
		
		if path == []
			raise ArgumentError.new("You must specify a class name with a namespace!")
		end
		
		directory = Files::Path.new('test') + path.join('/')
		directory.mkpath
		
		name = Build::Name.new(class_name)
		substitutions = target.context.substitutions.dup
		
		# e.g. Foo Bar, typically used as a title, directory, etc.
		substitutions['TEST_NAME'] = name.identifier
		substitutions['TEST_FILE_NAME'] = name.identifier
		
		substitutions['TEST_SUITE_NAME'] = name.identifier + "TestSuite"
		substitutions['TEST_SUITE_DESCRIPTION'] = full_class_name
		
		substitutions['TEST_SOURCE_HEADER'] = "#{full_class_name.gsub('::', '/')}.hpp"
		
		# e.g. foo-bar, typically used for targets, executables.
		substitutions['NAMESPACE'] = target.scope_for_namespace(path)
		
		source_path = Build::Files::Directory.new(target.package.path + "templates/test")
		generate source: source_path, prefix: directory, substitutions: substitutions
	end
end

# Configurations

define_configuration "development" do |configuration|
	configuration[:source] = "https://github.com/kurocha"
	
	configuration.import "unit-test"
	
	configuration.require "build-files"
	
	# Provides all the build related infrastructure:
	configuration.require 'platforms'
	
	# Provides some useful C++ generators:
	configuration.require 'generate-cpp-class'
	configuration.require 'generate-project'
	configuration.require 'generate-travis'
end

define_configuration "unit-test" do |configuration|
	configuration.public!
	
	configuration.require "streams"
end
