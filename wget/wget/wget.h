#define CURL_STATICLIB
#include <curl\curl.h>
#include <string>

#include "types.h"

class Wget
{
public:
	Wget();
	~Wget();

	bool download(const globalArgs_t& cmdArguments);

private:
	void* m_curl;
	bool m_verbosity;

	std::string getFileName(const std::string& url, const std::string& savedir);
	int readSubLinks(int level, std::string url);
	bool process(const std::string& url, int level);
};

