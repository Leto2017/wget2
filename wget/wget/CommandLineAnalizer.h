#pragma once

/**
 * @file        CommandLineAnalizer.h
 * @author      Kharisova Madina \<gkhmadina\@gmail.com\>
 * @date        28/04/2019
 * All rights reserved.
 */
#include <string>

#include "types.h"

struct option;

	class CommandLineAnalizer
	{
	public:
		//ctor
		CommandLineAnalizer(CommandLineAnalizer const&) = delete;
		//
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

		/*! Show the command line arguments suitable for wget
			\param[in] name of *.exe file
			\returns result - 
	   */
		void show_usage(std::string name);

		/*! Return setting of wget using getopt.h
			\param[in] name of *.exe file
			\returns result -
	   */
		globalArgs_t getCmdArgumentsObject();

		/*! Parse the input arguments using getopt.h
			\param[in] argc - number of input arguments of commana line
			\param[in] argv - values 
			\returns result - success or not
	   */
		bool setParameters(int argc, char** argv);

		static const struct option longOpts[];
		static const char* optString;
		
	private:
		CommandLineAnalizer() {}
	
		globalArgs_t globalArgs;
    };
