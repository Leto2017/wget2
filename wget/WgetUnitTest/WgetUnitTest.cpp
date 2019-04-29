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
		
		TEST_METHOD(Test1)
		{
			Wget *myClass = new Wget();
			Assert::IsTrue(myClass->download("kun.uz", 1));
		}

		TEST_METHOD(Test2)
		{
			TEST_CLASS testClass;
			int result = testClass.read("kun.uz");
			Assert::AreEqual(1, result);

		}

		TEST_METHOD(Test3)
		{
			TEST_CLASS testClass;
			int result = testClass.read("m_kun.uzv");
			returnCodeStruct codeStruct = testClass.getStatusCode();
			Assert::AreEqual(404, codeStruct.http_code);
		}

	};
}
