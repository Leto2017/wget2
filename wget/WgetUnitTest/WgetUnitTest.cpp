#include "pch.h"
#include "CppUnitTest.h"
#include "../wget/wget.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WgetUnitTest
{
	TEST_CLASS(WgetUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::string name = "Bill";
			
			Assert::AreEqual("1", "1");
		}
	};
}
