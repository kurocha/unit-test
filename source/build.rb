
add_library 'UnitTest' do
	def sources(environment)
		Pathname.glob(root + 'UnitTest/**/*.cpp')
	end
	
	def headers(environment)
		Pathname.glob(root + 'UnitTest/**/*.h')
	end
	
	def files(environment)
		Pathname.glob(root + "bin/*")
	end
end
