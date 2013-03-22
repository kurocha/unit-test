
compile_executable("unit-tests-test-runner") do
	def source_files(environment)
		FileList[root, "**/*.cpp"]
	end
end