
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

required_version "0.5"

define_target "unit-test" do |target|
	target.install do |environment|
		top = Teapot::Build.top(package.path)

		top.add_directory('source')
		top.add_directory('test')
		
		top.execute(:install, environment)
	end
	
	target.depends :platform
	target.depends "Language/C++11"
	
	target.provides "Library/unit-test" do
		append linkflags "-lUnitTest"
	end
end
