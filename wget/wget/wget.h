#define CURL_STATICLIB
/**
 * @file        wget.h
 * @author      Kharisova Madina \<gkhmadina\@gmail.com\>
 * @date        28/04/2019
 * All rights reserved.
 */
#include <curl\curl.h>
#include <string>

#include "types.h"
#include "parser_new.h"

class Wget
{
public:
	//ctor
	Wget();
	//dtor
	~Wget();

	/*! Download the content of html page. This is the start function of class
		\param[in] cmdArguments - configurations
		\returns result - success or not
	*/
	bool download(const globalArgs_t& cmdArguments);
	/*! Download the content of html page. This is the start function of class
		\param[in] url - address of page to download
		\param[in] level - levels in
		\returns -
	*/
	void setUrl(const string &url, int level);

private:
	void* m_curl;
	parser<string> m_parser;
	globalArgs_t m_cmdArg;
	returnCodeStruct m_returnCode;

	/*! Get file name look like the name of parsing url
		\param[in] url
		\returns file name
	*/
	string getFileName(const std::string& url);

	/*! Download images using libcurl from the html page if getImages is on
		\param[in] url
		\returns result - success or not
	*/
	bool downloadImages(const std::string& url);

	/*! Download the content of links inside the html page if recursive is on and level more than 1
		\param[in] url 
		\param[in] level
		\returns result - success or not
	*/
	bool readSubLinks(int level, const string& url);

	/*! Download the content using libcurl
		\param[in] url
		\returns result - flag to determine the result
	*/
	int read(const std::string& url);

	/*! Main function to analize result 
		\param[in] url
		\param[in] level
		\returns result - success or not
	*/
	bool process(const std::string& url, int level);

	/*! Returns the name of file that should be created
		\param[in] url
		\returns result - name of image file
	*/
	string getImageName(const string &url);
};

