
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

required_version "2.0"

define_project "Unit Test" do |project|
	project.add_author "Samuel Williams"
	project.license = "MIT License"

	project.version = "0.1.0"
end

define_target "unit-test" do |target|
	target.build do
		source_root = target.package.path + 'source'
		bin_root = target.package.path + 'bin'
		
		copy binaries: Files::Directory.new(bin_root)
		copy headers: Files::Glob.new(source_root, 'UnitTest/**/*.{h,hpp}')
		
		build static_library: "UnitTest",
			source_files: Files::Glob.new(source_root, 'UnitTest/**/*.cpp')
	end
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.provides "Library/UnitTest" do
		append linkflags {install_prefix + "lib/libUnitTest.a"}
		
		define Rule, "copy.unit-tests" do
			input :test_assets
			
			parameter :prefix, implicit: true do |arguments|
				environment[:install_prefix] + "test"
			end
			
			apply do |parameters|
				copy source: parameters[:test_assets], prefix: parameters[:prefix]
			end
		end
		
		define Rule, "run.unit-tests" do
			input :source_files
			
			parameter :tests
			parameter :arguments
			
			parameter :executable_file, implicit: true do |arguments|
				environment[:install_prefix] + "test" + "#{arguments[:tests]}-tests"
			end
			
			apply do |parameters|
				build executable: parameters[:tests],
					executable_file: parameters[:executable_file],
					source_files: parameters[:source_files]
				
				run executable: parameters[:tests],
					executable_file: parameters[:executable_file],
					arguments: parameters[:arguments]
			end
		end
	end
end

define_target "unit-test-tests" do |target|
	target.build do
		run tests: 'UnitTest', source_files: target.package.path.glob("test/UnitTest/**/*.cpp")
	end
	
	target.depends "Build/Clang"
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	target.depends "Library/UnitTest"
	
	target.provides "Test/UnitTest"
end

define_target "unit-test-generator" do |target|
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
		generate source: source_path, prefix: target.context.root, substitutions: substitutions
	end
end

define_configuration "test" do |configuration|
	configuration[:source] = "https://github.com/kurocha"
	
	configuration.require "platforms"
	configuration.require "build-files"
	
	configuration.require "generate-template"
end
