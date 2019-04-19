#include <iostream> 


#include "CommandLineAnalizer.h"

option longOpts[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "url", required_argument, NULL, 'u' },
	{ "level", required_argument, NULL, 'l' },
	{ "tries", required_argument, NULL, 't' },
	{ "infile", required_argument, NULL, 'i' },
	{ "savedir", required_argument, NULL, 's' },
	{ "verbose", no_argument, NULL, 'v' },
	{ "recursive", no_argument, NULL, 'r' },
	{ "no-parent", no_argument, NULL, 'n' },
	{ NULL, no_argument, NULL, 0 }
};

std::string optString = "hu:rl:t:n:i:s:v?";

CommandLineAnalizer::CommandLineAnalizer()
{
	returnCode.code = 0;
	globalArgs.recursive = false;
	globalArgs.noparent = false;
	globalArgs.verbosity = false;
	globalArgs.level = 1;
	globalArgs.tries = 1;
}


CommandLineAnalizer::~CommandLineAnalizer()
{
}

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
		<< "\t-v --verbose = печатать в stdout подробно производимые операции, без этого флага печатать только ошибки\n"
		<< "\t-h --help =  показать как использовать программу, выдать аргументы консоли\n"
		<< std::endl;
}
