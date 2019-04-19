#include "wget.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

//#include "test_parse2.cpp"
using namespace std;


size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
	string data((const char*)ptr, (size_t)size * nmemb);
	*((stringstream*)stream) << data << endl;
	return size * nmemb;
}

Wget::Wget()
{
	m_curl = curl_easy_init();
	m_verbosity = false;
}


Wget::~Wget()
{
	curl_easy_cleanup(m_curl);
}

bool Wget::download(const globalArgs_t& cmdArguments)
{
	m_verbosity = cmdArguments.verbosity;
	return process(cmdArguments.url, cmdArguments.level);
}

bool Wget::process(const std::string& url, int level)
{
	if (m_verbosity)
	{
		puts("Start downloading...");
	}
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
	std::stringstream out;
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &out);
	curl_easy_setopt(m_curl, CURLOPT_VERBOSE, m_verbosity ? 1 : 0);
	CURLcode res = curl_easy_perform(m_curl);
	if (res != CURLE_OK && m_verbosity) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		return false;
	}

	std::cout << out.str() << std::endl;

	return true;
}


std::string Wget::getFileName(const std::string &url, const std::string &savedir)
{
	if (m_verbosity)
	{
		puts("Get filename ... ");
	}

	std::string str = url;
	str.erase(std::remove_if(str.begin(), str.end(),
		[](unsigned char c) { return std::ispunct(c); }), str.end());
	
	if (!savedir.empty())
	{
		str = savedir + "/" + str;
	}

	str += ".html";
	if (m_verbosity)
		cout << "Filename: " << str << endl;
	return str;
}

int Wget::readSubLinks(int level, std::string url)
{
	std::vector<std::string> linkList;
	
	if (!linkList.empty())
	{
		for (string i : linkList)
		{
			process(i, level);
		}
	}

	return 0;
}
