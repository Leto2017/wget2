#define _CRT_SECURE_NO_DEPRECATE


#include <string>
#include "CommandLineAnalizer.h"

int main(int argc, char** argv)
{
	int opt = 0;

	int longIndex;
	opt = getopt_long(argc, argv, CommandLineAnalizer::optString, CommandLineAnalizer::longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
		case 'h':
		case '?':
			CommandLineAnalizer::show_usage(argv[0]);
			return 0;

		case 'u':
			CommandLineAnalizer::globalArgs.url = optarg;
			break;

		case 'l':
			CommandLineAnalizer::globalArgs.level = atoi(optarg);
			break;

		case 't':
			CommandLineAnalizer::globalArgs.tries = atoi(optarg);
			break;

		case 'i':
			CommandLineAnalizer::globalArgs.filename = static_cast<std::string>(optarg);
			break;

		case 's':
			CommandLineAnalizer::globalArgs.savedir = static_cast<std::string>(optarg);
			break;

		case 'n':
			CommandLineAnalizer::globalArgs.noparent = true;
			break;

		case 'r':
			CommandLineAnalizer::globalArgs.recursive = true;
			break;

		case 'v':
			CommandLineAnalizer::CommandLineAnalizer::globalArgs.verbosity = true;
			break;

		default:
			break;
		}

		opt = getopt_long(argc, argv, CommandLineAnalizer::optString, CommandLineAnalizer::longOpts, &longIndex);
	}
	return 0;
}