#pragma once
#include <string>

/**
 * @file        types.h
 * @author      Kharisova Madina \<gkhmadina\@gmail.com\>
 * @date        28/04/2019
 * All rights reserved. 
 */
static struct globalArgs_t
{
	std::string url;
	bool recursive;
	bool noparent;
	bool verbosity;
	bool getImages;
	int level;
	int tries;
	std::string filename;
	std::string savedir;

	globalArgs_t()
	{
		recursive = false;
		noparent = false;
		verbosity = true;
		getImages = false;
		level = 1;
		tries = 1;
	}
};

struct returnCodeStruct
{
	std::string error;
	std::string location;
	long http_code;

	returnCodeStruct()
	{
		http_code = 0;
	}
};