#define _CRT_SECURE_NO_DEPRECATE

#ifdef DOXYGEN
#define TEMP_DET_DEBUG   ///< turn on debug stdout output and dump clustering states into a text file
#define TEMP_DET_CLUSTS  ///< switch implementation of clustering method for RealTempDet
#endif


#include <string>
#include <iostream>

#include "wget.h"
#include "CommandLineAnalizer.h"

int main(int argc, char** argv)
{
	auto cmdAnalizer = CommandLineAnalizer::instance();
	bool setP = cmdAnalizer->setParameters(argc, argv);
	if (!setP)
		return 1;
	Wget downloader;
	bool result = downloader.download(cmdAnalizer->getCmdArgumentsObject());

	cerr << "RESULT: " << (result ? "YES" : "NO") << endl;
	
	return 0;
}
