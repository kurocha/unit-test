
compile_library 'UnitTest' do
	def source_files(environment)
		FileList[root, 'UnitTest/**/*.cpp']
	end
end

copy_headers do
	def source_files(environment)
		FileList[root, 'UnitTest/**/*.h']
	end
end

copy_files do
	def source_files(environment)
		FileList[root, 'bin/**/*']
	end
end
