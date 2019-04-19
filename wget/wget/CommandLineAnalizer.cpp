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
		<< "\t-l --level=<uint> = ������� ������������ ���������� ����� �� ������� �� ��������� ���������\n"
		<< "\t-t --tries=<uint> = ����� ������� ������� �������� �� ������ ������\n"
		<< "\t-n --no-parent    = ��������� �������� �� ���� �� �������� ��������\n"
		<< "\t-i --infile=<path> = ���� � �������� txt ����� �� ������� http-������\n"
		<< "\t-s --savedir=<path> = ���� �� �����, ��� ��������� html-��������\n"
		<< "\t-v --verbose = �������� � stdout �������� ������������ ��������, ��� ����� ����� �������� ������ ������\n"
		<< "\t-h --help =  �������� ��� ������������ ���������, ������ ��������� �������\n"
		<< std::endl;
}
