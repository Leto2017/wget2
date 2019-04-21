#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

using namespace std;

class parser
{

public:
	parser();

	void parse_link_r(vector<string> &, string);

	void parse_hostname(string, string &, string &, string &);

	void parse_img_link(vector<string> &, string);
};