#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

using namespace std;


/*!
* \file
* \author Deyneka N. (dina_ukr@mail.ru)
* \date   April, 2019
* \brief  HTML-page parser
*
* \section DESCRIPTION
*
* parser - class for searching links in html-page
*/

template <typename T>

class parser
{

public:
	parser() {};


	//--------------------------------------------------
	/// Method for recursive search for html-links
	///
	/// This function takes input string, searches links with tags "href" and 
	/// returns them to the link list.

	void parse_link_r(vector<T> &link_list, T string_to_parse)  
	{


		const char *rg_h = R"(<a\s*[^>]*href\s*=[^>]*>)"; 


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

	
	//--------------------------------------------------
	/// Method for making full path from html-links
	///
	/// In case of not full path it adds "head" before the path.


	void add_head(vector<T> &link_list, T head)
	{

		regex prot_regex("https{0,1}");

		smatch match;

		T tmp;

		for (size_t i = 0; i < link_list.size(); ++i)
		{
			tmp = link_list[i];

			regex_search(tmp, match, prot_regex);

			if (match.str() == "")
			{
				link_list[i] = head + link_list[i];
			}

		}

	}

	//--------------------------------------------------
	/// Method for parsing html-link
	///
	/// Input:
	///addr - address to parse
	///protocol - where to save protocol
	///hostname - where to save hostname
	///tail - where to save path from the hostname
	///prot - protocol to use in case of not full path
	///host - hostname to use in case of not full path

	void parse_hostname(T addr, T &protocol, T &hostname, T &tail, T prot, T host)
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

			hostname = match.prefix();
			tail = match.suffix();
		}
		else
		{
			hostname = host;
			tail = addr;

		}
	}


	//--------------------------------------------------
	/// Method for search for html-links to images
	///
	/// This function takes input string, searches links with tags "img" and 
	/// returns them to the link list. In case of not full path it adds "head" before the path.

	void parse_link_r(vector<T> &link_list, T string_to_parse, T head)
	{
		regex http_regex("<img.*src.*=.*\".*(?=\" )");

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
				tmp = http_match[i];

				if (regex_search(tmp, link_match, link_regex))
				{

					buf = link_match[1].str();

					regex_search(buf, match, prot_regex);

					if (match.str() == "")
					{
						buf = head + buf;
					}

					link_list.push_back(buf);


				}

			}
		}

	}
};


