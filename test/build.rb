
compile_executable("unit-tests-test-runner") do
	configure do
		linkflags ["-lUnitTest"]
	end
	
	def source_files(environment)
		FileList[root, "**/*.cpp"]
	end
end