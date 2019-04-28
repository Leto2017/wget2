#define CURL_STATICLIB
#include <curl\curl.h>
#include <string>

#include "types.h"
#include "parser_new.h"

class Wget
{
public:
	Wget();
	~Wget();

	bool download(const globalArgs_t& cmdArguments);

private:
	void* m_curl;
	parser<string> m_parser;
	globalArgs_t m_cmdArg;
	returnCodeStruct m_returnCode;

	string getFileName(const std::string& url);
	bool downloadImages(const std::string& url);
	bool readSubLinks(int level, const std::string& url);
	int read(const std::string& url);
	bool process(const std::string& url, int level);
	string getImageName(const string &url);
};

