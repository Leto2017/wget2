#define CURL_STATICLIB
#include <curl\curl.h>
#include <string>

#include "types.h"

#include <vector>
#include <iostream>
using namespace std;
template <typename T>
class parser_t
{

public:

	parser_t() {}

	void parse_link_r(std::vector<T>& s, T t)
	{
		cout << t << "\n";
	}

};

class Wget
{
public:
	Wget();
	~Wget();

	bool download(const globalArgs_t& cmdArguments);

private:
	void* m_curl;
	globalArgs_t m_cmdArg;
	returnCodeStruct m_returnCode;

	std::string getFileName(const std::string& url);
	bool downloadImages(const std::string& url);
	bool readSubLinks(int level, const std::string& url);
	int read(const std::string& url);
	bool process(const std::string& url, int level);
};

