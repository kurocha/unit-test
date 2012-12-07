
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

required_version "0.5"

define_package "unit-test" do |package|
	package.install do |environment|
		top = Teapot::Build.top(package.path)

		top.add_directory('source')
		top.add_directory('test')
		
		top.execute(:install, environment)
	end
	
	package.depends :system
	package.depends "Language/C++11"
	
	package.provides "Library/unit-test" do
		append linkflags "-lUnitTest"
	end
end
