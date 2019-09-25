# Unit Test

Unit Test is a modern C++ unit testing framework. It compiles multiple test suites into a single executable which can then be used to run unit tests. It uses several advanced features from C++11 including lambdas and initializer lists to improve the readability and reduce boiler plate code and macro usage.

[![Build Status](https://travis-ci.org/kurocha/unit-test.svg?branch=master)](https://travis-ci.org/kurocha/unit-test)

## Setup

Firstly the build tool `teapot` needs to be installed (which requires [Ruby][2]):
 
	$ gem install teapot

To run unit tests:

	$ teapot Test/UnitTest

[2]: http://www.ruby-lang.org/en/downloads/

## Usage

Typically, you'd create a directory called `test` and then, per component, create a file called `Test.Component.cpp`, e.g. `test/Test.UnitTest.cpp`. In this file, simply follow this template:

	namespace UnitTest
	{
		UnitTest::Suite StatisticsTestSuite {
			"UnitTest::Statistics",
	
			// Repeat this block as many times as required for various collections of unit tests.
			{"Basic pass and fail",
				[](UnitTest::Examiner & examiner) {
					UnitTest::Statistics statistics;
			
					statistics.pass_test();
					statistics.fail_test();
			
					examiner.expect(statistics.failed()).to(be_true);
				}
			},
		};
	}

Perhaps a canonical example would be to look at existing projects that use `unit-test`, including `unit-test` itself, [Tagged Format](https://github.com/kurocha/tagged-format) and [Euclid](https://github.com/kurocha/euclid).

### Migration

To migrate away from the `Test.*.cpp` prefix use the following shell:

```bash
for f in test/**/*.cpp; do echo mv "$f" "${f#Test.}"; done
```

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

## License

Released under the MIT license.

Copyright, 2013, by [Samuel G. D. Williams](http://www.codeotaku.com/samuel-williams).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
