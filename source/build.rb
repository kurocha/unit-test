
add_library 'UnitTest' do
	def sources
		Pathname.glob(root + 'UnitTest/**/*.cpp')
	end
	
	def headers
		Pathname.glob(root + 'UnitTest/**/*.h')
	end
	
	def files
		Pathname.glob(root + "bin/*")
	end
end
