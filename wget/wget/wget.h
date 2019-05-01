#define CURL_STATICLIB
/**
 * @file        wget.h
 * @author      Kharisova Madina \<gkhmadina\@gmail.com\>
 * @date        28/04/2019
 * All rights reserved.
 */
#include "curl\curl.h"
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

	/** Download the content of html page. This is the start function of class
		\param[in] cmdArguments - configurations
		\returns result - success or not
	*/
	bool download(const globalArgs_t& cmdArguments);
	/** Download the content of html page. This is the start function of class
		\param[in] url - address of page to download
		\param[in] level - levels in
		\returns - result - success or not
	*/
	bool download(const string &url, int level);

	/** Get code struct of last query
		\returns struct of code
	*/
	returnCodeStruct getStatusCode() const;

protected:
	void* m_curl;
	parser<string> m_parser;
	globalArgs_t m_cmdArg;
	returnCodeStruct m_returnCode;
	
	/** Get file name look like the name of parsing url
		\param[in] url
		\returns file name
	*/
	string getFileName(const string& url) const;

	/** Download images using libcurl from the html page if getImages is on
		\param[in] url
		\returns result - success or not
	*/
	bool downloadImages(const string& url) const;

	/** Download the content of links inside the html page if recursive is on and level more than 1
		\param[in] level
		\param[in] url 
		\returns result - success or not
	*/
	bool readSubLinks(int level, const string& url);

	/** Download the content using libcurl
		\param[in] url
		\returns result - flag to determine the result
	*/
	int read(const string& url);

	/** Main function to analize result 
		\param[in] url
		\param[in] level
		\returns result - success or not
	*/
	bool process(const string& url, int level);

	/** Returns the name of file that should be created
		\param[in] url
		\returns result - name of image file
	*/
	string getImageName(const string &url) const;
};

class TEST_CLASS : public Wget {
public:
	bool downloadImages(const string& url) {
		return Wget::downloadImages(url);
	}

	bool readSubLinks(int level, const string& url){
		return Wget::readSubLinks(level, url);
	}

	int read(const string& url) {
		return Wget::read(url);
	}

	bool process(const string& url, int level) {
		return Wget::process(url, level);
	}
};
