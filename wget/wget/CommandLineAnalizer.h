
#include <string>
#include <getopt.h>

//namespace CmdLineAnalizer
//{
	class CommandLineAnalizer
	{
	public:
		CommandLineAnalizer();
		~CommandLineAnalizer();

		static void show_usage(std::string name);
		static const struct option longOpts[];
		static const char* optString;

		static struct globalArgs_t
		{
			std::string url;
			bool recursive;
			bool noparent;
			bool verbosity;
			int level;
			int tries;
			std::string filename;
			std::string savedir;
		} globalArgs;


		static struct returnCodeStruct
		{
			std::string error;
			std::string location;
			int code;
		} returnCode;

	};
//}
