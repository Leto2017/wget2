#define _CRT_SECURE_NO_WARNINGS


#include "wget.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <direct.h>
#include <fstream>
#include <Windows.h>

using namespace std;


size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
	((string*)stream)->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

size_t callbackfunction(void* ptr, size_t size, size_t nmemb, void* userdata)
{
	FILE* stream = (FILE*)userdata;
	if (!stream)
		return 0;
	
	size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
	stream = NULL;
	return written;
}

Wget::Wget()
{
	m_curl = curl_easy_init();
	_ASSERTE(m_curl);
}


Wget::~Wget()
{
	curl_easy_cleanup(m_curl);
}

bool Wget::download(const string& url, int level)
{
	m_cmdArg.url = url;
	m_cmdArg.recursive = true;
	m_cmdArg.level = level;
	return process(m_cmdArg.url, level);
}

bool Wget::download(const globalArgs_t& cmdArguments)
{
	m_cmdArg = cmdArguments;
	if (m_cmdArg.url.empty() && m_cmdArg.verbosity)
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
			if (tries == 0 && (m_returnCode.http_code > 300))
				return false;
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
	else if (success == 0 || success == 2)
	{
		if (m_cmdArg.getImages)
		{
			std::vector<std::string> linkList;
			string filename = getFileName(url);
			std::ifstream ifs(filename);
			std::string content((std::istreambuf_iterator<char>(ifs)),
				(std::istreambuf_iterator<char>()));
			m_parser.parse_img_link(linkList, content, url);
			if (!linkList.empty())
			{
				for (string i : linkList)
				{
					cerr << i << endl;
					downloadImages(i);
				}
			}

		}
	}

	return true;
}


std::string Wget::getFileName(const std::string &url) const
{
	if (m_cmdArg.verbosity)
	{
		puts("Get filename ... ");
	}

	string str;
	if (m_cmdArg.filename.empty())
	{
		str = url;
		str.erase(std::remove_if(str.begin(), str.end(),
			[](unsigned char c) { return std::ispunct(c); }), str.end());
	}
	else
	{
		str = m_cmdArg.filename;
	}

	if (!m_cmdArg.savedir.empty())
	{
		if (CreateDirectory(m_cmdArg.savedir.c_str(), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			str = m_cmdArg.savedir + "/" + str;
		}
	}
	
	str += ".html";
	if (m_cmdArg.verbosity)
		cout << "Filename: " << str << endl;
	return str;
}

bool Wget::readSubLinks(int level, const string& url)
{
	vector<string> linkList;
	string filename = getFileName(url);
	std::ifstream ifs(filename);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	m_parser.parse_link_r(linkList, content);
	m_parser.add_head(linkList, url);

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
		cerr << url << endl;
	}

	char errbuf[CURL_ERROR_SIZE];
	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, errbuf);
	errbuf[0] = 0;
	curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
	string out;
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &out);
	CURLcode res = curl_easy_perform(m_curl);
	m_returnCode.http_code = 0;
	curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &m_returnCode.http_code);

	m_returnCode.error = errbuf;
	m_returnCode.curlCode = res;

	if (res != CURLE_OK) {
		size_t len = strlen(errbuf);
		fprintf(stderr, "\nlibcurl: (%d) ", res);
		if (len)
			fprintf(stderr, "%s%s", errbuf,
			((errbuf[len - 1] != '\n') ? "\n" : ""));
		else
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
	}

	char* redirect_url = NULL;
	curl_easy_getinfo(m_curl, CURLINFO_REDIRECT_URL, &redirect_url);
	if (redirect_url)
		m_returnCode.location = redirect_url;

	redirect_url = NULL;
	if (res != CURLE_OK)
		return false;
	
	bool ok = false;
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
		ok = true;
	}
	if (m_cmdArg.verbosity)
	{
		fprintf(stderr, "\nCODE: (%d) ", m_returnCode.http_code);
	}

	string filename = getFileName(url);
	ofstream file;
	file.open(filename);
	file << out;

	file.close();

	if (ok)
	{
		if (m_cmdArg.verbosity)
			fprintf(stderr, "\nStatus code: (%d ) recursive with level %d \n", m_returnCode.http_code, m_cmdArg.level);
		return 2;
	}
	return 0;
}

string Wget::getImageName(const string& url) const
{
	if (m_cmdArg.verbosity)
	{
		puts("Get image filename ... ");
	}

	std::size_t found = url.find_last_of("/\\");
	string str = url.substr(found + 1);
	
	if (!m_cmdArg.savedir.empty())
	{
		if (CreateDirectory(m_cmdArg.savedir.c_str(), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			str = m_cmdArg.savedir + "/" + str;
		}
	}
	return str;
}
bool Wget::downloadImages(const std::string& url) const
{
	if (m_cmdArg.verbosity)
	{
		puts("Start downloading image...");
	}
	string image_name = getImageName(url);
	FILE* fp = fopen(image_name.c_str(), "wb");
	if (!fp)
	{
		fprintf(stderr, "Failed to create file on the disk\n");
		return false;
	}

	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, callbackfunction);
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);

	CURLcode rc = curl_easy_perform(m_curl);
	if (rc)
	{
		fprintf(stderr, "Failed to download: %s\n", url.c_str());
		return false;
	}

	long res_code = 0;
	curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &res_code);
	if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
	{
		fprintf(stderr, "Response code: %d\n", res_code);
		return false;
	}

	fclose(fp);

	return true;
}

returnCodeStruct Wget::getStatusCode() const
{
	return m_returnCode;
}