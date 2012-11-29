
add_executable("unit-tests-test-runner") do
	configure do
		linkflags ["-lUnitTest"]
	end
	
	def sources(environment)
		FileList[root, "**/*.cpp"]
	end
end