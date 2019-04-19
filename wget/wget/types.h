#pragma once
#include <string>

struct globalArgs_t
{
	std::string url;
	bool recursive;
	bool noparent;
	bool verbosity;
	int level;
	int tries;
	std::string filename;
	std::string savedir;

	globalArgs_t()
	{
		recursive = false;
		noparent = false;
		verbosity = false;
		level = 1;
		tries = 1;
	}
};

struct returnCodeStruct
{
	std::string error;
	std::string location;
	int code;

	returnCodeStruct()
	{
		code = 0;
	}
};