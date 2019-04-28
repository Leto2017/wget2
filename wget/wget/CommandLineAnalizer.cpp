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
		<< "\t-l --level=<uint> = глубина рекурсивного скачивания сайта по ссылкам на скачанных страницах\n"
		<< "\t-t --tries=<uint> = число попыток скачать страницу до выдачи ошибки\n"
		<< "\t-n --no-parent    = загружать страницы не выше по иерархии заданной\n"
		<< "\t-i --infile=<path> = путь к входному txt файлу со списком http-ссылок\n"
		<< "\t-s --savedir=<path> = путь до папки, где сохранять html-страницы\n"
		<< "\t-g --getimages = закачивать картинки с html страницы\n"
		<< "\t-v --verbose = печатать в stdout подробно производимые операции, без этого флага печатать только ошибки\n"
		<< "\t-h --help =  показать как использовать программу, выдать аргументы консоли\n"
		<< std::endl;
}

globalArgs_t CommandLineAnalizer::getCmdArgumentsObject()
{
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
