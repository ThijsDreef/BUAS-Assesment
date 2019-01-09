#include "System/Engine/options.h"

Options::Options(std::vector<OptionData> startOptions)
{
    for (unsigned int i = 0; i < startOptions.size(); i++)
        options[startOptions[i].first] = startOptions[i].second;
}

Options::~Options()
{

}

void Options::saveOptions(const std::string & fileName)
{
    std::fstream optionsFile(fileName, std::ios::out | std::ios::trunc);
    for (auto & opt : options) 
    {
        optionsFile << opt.first << "=" << opt.second << "\n";
    }  
    optionsFile.close();
}

void Options::loadOptions(const std::string & fileName)
{
    std::fstream optionsFile(fileName, std::ios::in);
    std::string line;
    while (std::getline(optionsFile, line))
    {
        int found = line.find("=");
        if (found == 0) continue;
        options[line.substr(0, found)] = line.substr(found + 1, line.length());
    }
    optionsFile.close();
}

const std::string & Options::getOption(const std::string & name)
{
    return options[name];
}

int Options::getOptionI(const std::string & name)
{
    return atoi(options[name].c_str());
}

bool Options::getOptionB(const std::string & name)
{
    return atoi(options[name].c_str()) > 0;
}

void Options::setOption(const OptionData & option)
{
    options[option.first] = option.second;
}