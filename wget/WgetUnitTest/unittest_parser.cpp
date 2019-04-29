#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "../test/parser_doxygen.h" //тут надо прописать другой путь при присоединении к проекту

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserUnitTest
{		
	TEST_CLASS(ParserUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethodParseLink)
		{
			std::vector<string> vec;
			std::string tag = "<noscript><div><a href=\"https://mc.yandex.ru/watch/22022599\">";
			std::string res = "https://mc.yandex.ru/watch/22022599";

			parser<string> p;

			p.parse_link_r(vec, tag);

			Assert::AreEqual(res, vec[0]);
		}

		TEST_METHOD(TestMethodParseImg)
		{
			std::vector<string> vec;
			std::string tag = "<noscript><div><img src=\"https://mc.yandex.ru/watch/22022599\">";
			std::string res = "https://mc.yandex.ru/watch/22022599";

			parser<string> p;

			std::string h = "http://yandex.ru";

			p.parse_img_link(vec, tag, h);

			Assert::AreEqual(res, vec[0]);
		}

		TEST_METHOD(TestMethodParseHostname)
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

		TEST_METHOD(TestMethodAddhead)
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