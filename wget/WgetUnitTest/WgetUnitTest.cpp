#define CURL_STATICLIB
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
			Assert::AreEqual(1, 1);
			Wget *myClass = new Wget();
			Assert::IsTrue(myClass->setUrl("kun.uz", 1));
		}
	};
}
