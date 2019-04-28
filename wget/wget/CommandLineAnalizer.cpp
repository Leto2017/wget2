#include <iostream> 
#include <getopt.h>

#include "CommandLineAnalizer.h"

const option CommandLineAnalizer::longOpts[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "url", required_argument, NULL, 'u' },
	{ "level", required_argument, NULL, 'l' },
	{ "tries", required_argument, NULL, 't' },
	{ "infile", required_argument, NULL, 'i' },
	{ "savedir", required_argument, NULL, 's' },
	{ "verbose", no_argument, NULL, 'v' },
	{ "recursive", no_argument, NULL, 'r' },
	{ "getimages", no_argument, NULL, 'im' },
	{ "no-parent", no_argument, NULL, 'n' },
	{ NULL, no_argument, NULL, 0 }
};

const char* CommandLineAnalizer::optString = "hu:rl:t:n:i:s:g:v?";

void CommandLineAnalizer::show_usage(std::string name)
{
	std::cerr << "Usage: <option(s)> SOURCES"
		<< "Options:\n"
		<< "\t-u --url=<string> = the http-address to download web-page\n"
		<< "\t-r --recursive       = load pages by links found in the download pages\n"
		<< "\t-l --level=<uint> = depth of recursive webpages download by links from downloaded pages\n"
		<< "\t-t --tries=<uint> = the number of attempts to download the page before issuing an error\n"
		<< "\t-n --no-parent    = load pages no higher than a given hierarchy\n"
		<< "\t-i --infile=<path> = path to the input txt-file with the list of http-links\n"
		<< "\t-s --savedir=<path> = path to the directory where html-page is stored\n"
		<< "\t-g --getimages = download images from html-page\n"
		<< "\t-v --verbose = print to stdout detailed operations, without this flag, print only errors\n"
		<< "\t-h --help =  show how to use the program, give console arguments\n"
		<< std::endl;
}

globalArgs_t CommandLineAnalizer::getCmdArgumentsObject()
{
	//globalArgs.url = "kun.uz";
	return globalArgs;
}

bool CommandLineAnalizer::setParameters(int argc, char** argv)
{
#pragma region getopt
	int opt = 0;

	int longIndex;
	opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
		case 'h':
		case '?':
			show_usage(argv[0]);
			return false;

		case 'u':
			globalArgs.url = optarg;
			break;

		case 'l':
			globalArgs.level = atoi(optarg);
			break;

		case 't':
			globalArgs.tries = atoi(optarg);
			break;

		case 'i':
			globalArgs.filename = static_cast<std::string>(optarg);
			break;

		case 's':
			globalArgs.savedir = static_cast<std::string>(optarg);
			break;

		case 'n':
			globalArgs.noparent = true;
			break;

		case 'r':
			globalArgs.recursive = true;
			break;

		case 'g':
			globalArgs.getImages = true;
			break;

		case 'v':
			globalArgs.verbosity = true;
			break;

		default:
			break;
		}

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}
	return true;
#pragma endregion
}
