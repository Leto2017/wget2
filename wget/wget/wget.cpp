#define _CRT_SECURE_NO_WARNINGS


#include "wget.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <direct.h>
#include <fstream>
#include "parser_new.h"
using namespace std;


size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
	string data((const char*)ptr, (size_t)size * nmemb);
	*((stringstream*)stream) << data << endl;
	return size * nmemb;
}

size_t callbackfunction(void* ptr, size_t size, size_t nmemb, void* userdata)
{
	FILE* stream = (FILE*)userdata;
	if (!stream)
	{
		printf(" No stream\n");
		return 0;
	}

	size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
	return written;
}

Wget::Wget()
{
	m_curl = curl_easy_init();
}


Wget::~Wget()
{
	curl_easy_cleanup(m_curl);
}

bool Wget::download(const globalArgs_t& cmdArguments)
{
	m_cmdArg = cmdArguments;
	if (m_cmdArg.url.empty())
	{
		puts("Put Url to process");
		return false;
	}
	return process(cmdArguments.url, m_cmdArg.level);
}

bool Wget::process(const std::string& url, int level)
{
	int tries = m_cmdArg.tries;
	int success = read(url);
	if (success == 1)
	{
		if (m_returnCode.http_code > 0 && (tries > 0))
		{
			if (m_cmdArg.verbosity)
			{
				cout << "New location " << m_returnCode.location << endl;
				cout << "Attempt number: " << tries << endl;
			}
			tries -= 1;
			process(m_returnCode.location, level);
		}
		return true;
	}
	else if (success == 2)
	{
		if (level - 1 != 0)
		{
			int ok = readSubLinks(level - 1, url);
		}
	}
	else if (success == 3)
	{
		if (url == m_cmdArg.url)
			return true;
	}

	return true;
}


std::string Wget::getFileName(const std::string &url)
{
	if (m_cmdArg.verbosity)
	{
		puts("Get filename ... ");
	}

	std::string str = url;
	str.erase(std::remove_if(str.begin(), str.end(),
		[](unsigned char c) { return std::ispunct(c); }), str.end());
	
	if (!m_cmdArg.savedir.empty())
	{
		str = m_cmdArg.savedir + "/" + str;
	}

	str += ".html";
	if (m_cmdArg.verbosity)
		cout << "Filename: " << str << endl;
	return str;
}

bool Wget::readSubLinks(int level, const std::string& url)
{
	std::vector<std::string> linkList;

	
	if (!linkList.empty())
	{
		for (string i : linkList)
		{
			process(i, level);
		}
	}

	return true;
}

int Wget::read(const std::string& url)
{
	if (m_cmdArg.verbosity)
	{
		puts("Start downloading...");
	}

	char errbuf[CURL_ERROR_SIZE];
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	//curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, errbuf);
	errbuf[0] = 0;
	curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
	std::stringstream out;
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &out);
	//curl_easy_setopt(m_curl, CURLOPT_VERBOSE, m_cmdArg.verbosity ? 1 : 0);
	CURLcode res = curl_easy_perform(m_curl);
	m_returnCode.http_code = 0;
	curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &m_returnCode.http_code);
	if (res != CURLE_OK) {
		size_t len = strlen(errbuf);
		fprintf(stderr, "\nlibcurl: (%d) ", res);
		if (len)
			fprintf(stderr, "%s%s", errbuf,
			((errbuf[len - 1] != '\n') ? "\n" : ""));
		else
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
		return false;
	}

	char* redirect_url = NULL;
	curl_easy_getinfo(m_curl, CURLINFO_REDIRECT_URL, &redirect_url);
	if (redirect_url)
		m_returnCode.location = redirect_url;

	if (m_returnCode.http_code >= 500 && m_returnCode.http_code < 600)
	{
		if (m_cmdArg.verbosity)
			fprintf(stderr, "\nStatus code: (%d) ", m_returnCode.http_code);
		return 3;
	}
	else if (m_returnCode.http_code >= 300 && m_returnCode.http_code < 400)
	{
		if (m_cmdArg.verbosity)
			fprintf(stderr, "\nStatus code: (%d) ", m_returnCode.http_code);
		return 1;
	}
	else if (m_returnCode.http_code == 200 && m_cmdArg.recursive && m_cmdArg.level > 1)
	{
		if (m_cmdArg.verbosity)
			fprintf(stderr, "\nStatus code: (%d ) recursive with level %d", m_returnCode.http_code, m_cmdArg.level);
		return 2;
	}
	if (m_cmdArg.verbosity)
	{
		fprintf(stderr, "\nCODE: (%d) ", m_returnCode.http_code);
	}

	if (!m_cmdArg.savedir.empty())
	{
		const int dir = _mkdir(m_cmdArg.savedir.c_str());
	}
	string filename = getFileName(url);
	ofstream file;
	file.open(filename);
	file << out.str();

	file.close();

	return 0;
}


bool Wget::downloadImages(const std::string& url)
{
	string image_name;
	FILE* fp = fopen(image_name.c_str(), "wb");
	if (!fp)
	{
		fprintf(stderr, "Failed to create file on the disk\n");
		return false;
	}

	CURL* curlCtx = curl_easy_init();
	curl_easy_setopt(curlCtx, CURLOPT_URL, url);
	curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
	curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

	CURLcode rc = curl_easy_perform(curlCtx);
	if (rc)
	{
		fprintf(stderr, "Failed to download: %s\n", url.c_str());
		return false;
	}

	long res_code = 0;
	curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
	if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
	{
		fprintf(stderr, "Response code: %d\n", res_code);
		return false;
	}

	curl_easy_cleanup(curlCtx);

	fclose(fp);

	return true;
}