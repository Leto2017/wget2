#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

using namespace std;


template <typename T>

class parser
{

public:
	parser() {};

	void parse_link_r(vector<T> &link_list, T string_to_parse)
	{

		//const char *rg = R"((http|ftp|https)://([\w_-]+(?:(?:\.[\w_-]+)+))([\w.,@?^=%&:/~+#-]*[\w@?^=%&/~+#-])?)";

		const char *rg_h = R"(<a\s*[^>]*href\s*=[^>]*>)";

		//const char *rg = "(https{0,1}:\/){0,1}\/+.*(?=\" )";

		const char *rg = ("\"([^\"]+)\"");

		regex http_regex(rg_h);
		regex link_regex(rg);


		smatch http_match;
		smatch link_match;

		T tmp;

		T tmps = string_to_parse;


		while (regex_search(tmps, http_match, http_regex))
		{
			tmp = http_match.str();

			tmps = http_match.suffix();

			if (regex_search(tmp, link_match, link_regex))
			{
				link_list.push_back(link_match[1].str());
			}

		}

	}
	
	void parse_hostname(T addr, T &protocol, T &hostname, T &tail, T prot, T host )
	{
		regex prot_regex("https{0,1}");

		regex host_regex("://");
		regex host2_regex("/");

		T tmp;

		tmp = addr;

		smatch match;

		regex_search(tmp, match, prot_regex);

		protocol = match[0];

		if (protocol == "")
		{
			protocol = prot;

			tmp = addr;
		}
		else 
			tmp = match.suffix();

		regex_search(tmp, match, host_regex);

		if (match.str() != "")
		{
			tmp = match.suffix();

			regex_search(tmp, match, host2_regex);

			hostname = match.prefix();  //тут надо убирать www или нет?
			tail = match.suffix();
		}
		else
		{
			hostname = host;
			tail = addr;

		}
	}

	void parse_img_link(vector<T> &link_list, T string_to_parse, T head)
	{
		regex http_regex("<img.*src.*=.*\".*(?=\" )");

		//regex link_regex("(https{0,1}:/){0,1}/+.*(?=\" )");
		
		regex link_regex("\"([^\"]+)\"");

		regex prot_regex("https{0,1}");

		smatch http_match;
		smatch link_match;
		smatch match;

		T tmp;
		string buf;

		if (regex_search(string_to_parse, http_match, http_regex))
		{

			for (size_t i = 0; i < http_match.size(); ++i)
			{
				tmp = http_match[i].str();
				if (regex_search(tmp, link_match, link_regex))
				{

					buf = link_match[1].str();

					regex_search(buf, match, prot_regex);

					if (match.str() == "")
					{
						buf = head + buf;
					}

					link_list.push_back(buf);

					/*for (size_t j = 0; j < link_match.size(); ++j)
					{
						if (link_match[j].matched)
						{
							buf = link_match[j];
							link_list.push_back(link_match[j]);
						}

					}*/
				}

			}
		}

	}
};
