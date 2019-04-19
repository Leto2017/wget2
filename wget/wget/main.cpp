#define _CRT_SECURE_NO_DEPRECATE


#include <string>
#include <iostream>

#include "wget.h"
#include "CommandLineAnalizer.h"

int main(int argc, char** argv)
{
	auto cmdAnalizer = CommandLineAnalizer::instance();
	cmdAnalizer->setParameters(argc, argv);
	Wget downloader;
	bool result = downloader.download(cmdAnalizer->getCmdArgumentsObject());
	
	return 0;
}