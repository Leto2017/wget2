#include <iostream> 


#include "CommandLineAnalizer.h"

/*option longOpts[] = {
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
*/
std::string optString = "hu:rl:t:n:i:s:v?";

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

globalArgs_t CommandLineAnalizer::getCmdArgumentsObject()
{
	globalArgs.url = "google.com";
	return globalArgs;
}

void CommandLineAnalizer::setParameters(int argc, char** argv)
{
#pragma region getopt
	/*int opt = 0;

	int longIndex;
	opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
		case 'h':
		case '?':
			show_usage(argv[0]);
			return 0;

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

		case 'v':
			CommandLineAnalizer::globalArgs.verbosity = true;
			break;

		default:
			break;
		}

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}*/
#pragma endregion
}
