
add_library 'UnitTest' do
	def sources(environment)
		FileList[root, 'UnitTest/**/*.cpp']
	end
	
	def headers(environment)
		FileList[root, 'UnitTest/**/*.h']
	end
	
	def files(environment)
		FileList[root, 'bin/**/*']
	end
end
