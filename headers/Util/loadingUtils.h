#ifndef UTIL__
#define UTIL__
#include <vector>
#include <fstream>

namespace UtilLoader
{
  void loadFile(std::vector<char>& buffer, const std::string& filename);
	void loadFile(std::vector<unsigned char>& buffer, const std::string& filename);
} /* Util */

#endif