#define CURL_STATICLIB
#include "pch.h"
#include "CppUnitTest.h"
#include "../wget/wget.h"

#include "../wget/parser_new.h"
#include "stdafx.h"
#include <vector>

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
			Assert::AreEqual(int(CURLE_OK), codeStruct.curlCode);
		}
		
		TEST_METHOD(Test4)
		{
			std::vector<string> vec;
			std::string tag = "<noscript><div><a href=\"https://mc.yandex.ru/watch/22022599\">";
			std::string res = "https://mc.yandex.ru/watch/22022599";

			parser<string> p;

			p.parse_link_r(vec, tag);

			Assert::AreEqual(res, vec[0]);
		}

		TEST_METHOD(Test5)
		{
			std::vector<string> vec;
			std::string tag = "<noscript><div><img src=\"https://mc.yandex.ru/watch/22022599\">";
			std::string res = "https://mc.yandex.ru/watch/22022599";

			parser<string> p;

			std::string h = "http://yandex.ru";

			p.parse_img_link(vec, tag, h);

			Assert::AreEqual(res, vec[0]);
		}

		TEST_METHOD(Test6)
		{
			std::string tag = "https://mc.yandex.ru/watch/22022599";

			parser<string> p;

			std::string protocol;
			std::string hostname;
			std::string tail;

			std::string e_protocol = "https";
			std::string e_hostname = "mc.yandex.ru";
			std::string e_tail = "watch/22022599";

			p.parse_hostname(tag,protocol,hostname,tail,"https","yandex.ru");

			Assert::AreEqual(e_protocol, protocol);
			Assert::AreEqual(e_hostname, hostname);
			Assert::AreEqual(e_tail, tail);
		}

		TEST_METHOD(Tes7)
		{
			parser<string> p;

			std::vector<string> vec;
			
			vec.push_back("/watch/22022599");

			std::string res = "https://mc.yandex.ru/watch/22022599";

			std::string h = "https://mc.yandex.ru";

			p.add_head(vec, h);

			Assert::AreEqual(res, vec[0]);
		}


	};
}
