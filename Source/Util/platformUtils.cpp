#include "util/platformUtils.h"

namespace PlatformUtils
{
  #ifdef WINDOWS
  void readDirectory(const std::string& name, std::vector<std::string> & vector)
  {
      std::string pattern(name);
      pattern.append("\\*");
      WIN32_FIND_DATA data;
      HANDLE hFind;
      if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
          do {
              vector.push_back(data.cFileName);
          } while (FindNextFile(hFind, &data) != 0);
          FindClose(hFind);
      }
  }
  #endif
}