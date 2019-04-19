#include "wget.h"
#include <sstream>
#include <iostream>
using namespace std;


size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
	string data((const char*)ptr, (size_t)size * nmemb);
	*((stringstream*)stream) << data << endl;
	return size * nmemb;
}

Wget::Wget()
{
	curl = curl_easy_init();
}


Wget::~Wget()
{
	curl_easy_cleanup(curl);
}

std::string Wget::download(const globalArgs_t& cmdArguments)
{
	if (cmdArguments.verbosity)
	{
		puts("Start downloading...");
	}
	curl_easy_setopt(curl, CURLOPT_URL, cmdArguments.url.c_str());
	/* example.com is redirected, so we tell libcurl to follow redirection */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
	curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
	std::stringstream out;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, cmdArguments.verbosity ? 1 : 0);
	/* Perform the request, res will get the return code */
	CURLcode res = curl_easy_perform(curl);
	/* Check for errors */
	if (res != CURLE_OK && cmdArguments.verbosity) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
	}
	return out.str();
}
