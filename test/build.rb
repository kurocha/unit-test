
add_executable("unit-tests-test-runner") do
	configure do
		ldflags {["-L", File.join(install_prefix, "lib"), "-lUnitTest"]}
		buildflags {["-I", File.join(install_prefix, "include")]}
	end
	
	def sources
		Pathname.glob(root + "**/*.cpp")
	end
end