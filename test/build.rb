
add_executable("unit-tests-test-runner") do
	configure do
		linkflags ["-lUnitTest"]
	end
	
	def sources
		Pathname.glob(root + "**/*.cpp")
	end
end