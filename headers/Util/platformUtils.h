#ifndef PLATFORMUTILS__
#define PLATFORMUTILS__
#include <fstream>
#include <vector>

#define WINDOWS

#ifdef WINDOWS
  #include <Windows.h>
#endif

namespace PlatformUtils 
{
  void readDirectory(const std::string & name, std::vector<std::string> & vector);
};

#endif