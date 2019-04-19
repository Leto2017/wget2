#define CURL_STATICLIB
#include <curl\curl.h>
#include <string>

#include "types.h"

class Wget
{
public:
	Wget();
	~Wget();

	std::string download(const globalArgs_t& cmdArguments);

private:
	void* curl;
};

