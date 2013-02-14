
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

required_version "0.6"

define_target "unit-test" do |target|
	target.install do |environment|
		install_directory(package.path, 'source', environment)
	end
	
	target.depends :platform
	target.depends "Language/C++11"
	
	target.provides "Library/UnitTest" do
		append linkflags "-lUnitTest"
	end
end

define_target "unit-test-tests" do |target|
	target.install do |environment|
		install_directory(package.path, 'test', environment)
	end
	
	target.depends :platform
	target.depends "Language/C++11"
	target.depends "Library/UnitTest"
	
	target.provides "Test/UnitTest"
end
