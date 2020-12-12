#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;
#include <map>;


class Utils
{
	public:
		Utils();
		void loadCfg(const string& cfgFile);
		string getCfgVal(string str);
private:
	map<string, string> cfg;
};

