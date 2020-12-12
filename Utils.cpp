#include "Utils.h"


Utils::Utils()
{
    this->loadCfg("boardGame.cfg");
    string secCfgFileName = cfg["gameName"] + ".cfg";
    this->loadCfg(secCfgFileName);
}

void loadCfgHelper() {

}

void Utils::loadCfg(const string& cfgFile)
{
    // std::ifstream is RAII, i.e. no need to call close
    ifstream cFile(cfgFile);
    if (cFile.is_open())
    {
        std::string line;
        while (getline(cFile, line)) {
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                line.end());
            if (line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            auto key = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);

            cfg[key] = value;
        }
    }
    else {
        cerr << "Couldn't open config file for reading. Please provide " << cfgFile << "\n";
    }
}

string Utils::getCfgVal(string strKey)
{
    return cfg[strKey];;
}
