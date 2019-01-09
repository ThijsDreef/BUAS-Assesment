#ifndef OPTIONS__
#define OPTIONS__

#include <fstream>
#include <map>
#include <vector>
#include <string>

typedef std::pair<std::string, std::string> OptionData;

class Options 
{
private:
  std::map<std::string, std::string> options;
public:
  Options(std::vector<OptionData> startOptions);
  ~Options();
  void saveOptions(const std::string & fileName);
  void loadOptions(const std::string & fileName);
  const std::string & getOption(const std::string & name);
  int getOptionI(const std::string & name);
  bool getOptionB(const std::string & name);
  void setOption(const OptionData & option);
};

#endif