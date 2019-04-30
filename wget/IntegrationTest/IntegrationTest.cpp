#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include "../wget/wget.h"


using namespace std;

void removeSpaces(string &input)
{
	//input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
}

int main()
{
	string str = string("C:/GnuWin32/bin/wget --no-check-certificate cplusplus.com");

	const char* x = str.c_str();
	system(x);
	Wget wget;
	globalArgs_t globArgs;
	globArgs.filename = "index";
	globArgs.url = "cplusplus.com";
	globArgs.savedir = "C:/madina";

	wget.download(globArgs);

	setlocale(LC_ALL, "rus");
	ifstream fin1("index.html");
	std::string contentGNUwget((std::istreambuf_iterator<char>(fin1)),
		(std::istreambuf_iterator<char>()));
	fin1.close();

	ifstream fin2("C:/madina/index.html");
	std::string contentCustomWget((std::istreambuf_iterator<char>(fin2)),
		(std::istreambuf_iterator<char>()));
	fin2.close();

	if (!contentGNUwget.empty() && contentCustomWget.empty())
	{
		puts("Custom class didn't get anything");
	}
	else if (!contentGNUwget.empty() && !contentCustomWget.empty())
	{
		removeSpaces(contentGNUwget);
		removeSpaces(contentCustomWget);
		for (int i = 0; i < contentCustomWget.size(); ++i)
		{
			if (contentCustomWget[i] != contentGNUwget[i])
				cout << contentCustomWget[i] << contentGNUwget[i] << endl;
		}
		if (contentCustomWget == contentGNUwget)
			puts("EQUAL - excellent");
		else
			puts("Sth goes wrong");
	}
	else if (contentGNUwget.empty() && !contentCustomWget.empty())
	{
		puts("very stramge");
	}

	return 0;

}