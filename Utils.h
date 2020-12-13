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
		string getCfgVal(string strKey);
		int getCfgValInt(string strKey);
private:
	map<string, string> cfg;
};

