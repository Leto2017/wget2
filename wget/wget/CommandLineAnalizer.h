
#include <string>
//#include <getopt.h>

#include "types.h"

	class CommandLineAnalizer
	{
	public:
		CommandLineAnalizer(CommandLineAnalizer const&) = delete;
		CommandLineAnalizer& operator=(CommandLineAnalizer const&) = delete;

		/*However there are times with multiple static objects where you need to be able to guarantee that the singleton 
		will not be destroyed until all your static objects that use the singleton no longer need it.
		In this case std::shared_ptr can be used to keep the singleton alive for all users even when 
		the static destructors are being called at the end of the program:*/
		static std::shared_ptr<CommandLineAnalizer> instance()
		{
			static std::shared_ptr<CommandLineAnalizer> s{ new CommandLineAnalizer };
			return s;
		}

		void show_usage(std::string name);
		globalArgs_t getCmdArgumentsObject();
		/*static const struct option longOpts[];*/
		const char* optString;
		void setParameters(int argc, char** argv);
	
	private:
		CommandLineAnalizer() {}
	
		globalArgs_t globalArgs;
        returnCodeStruct returnCode;

	};
