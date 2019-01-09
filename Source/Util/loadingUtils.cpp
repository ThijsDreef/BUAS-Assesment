#include "Util/loadingUtils.h"

namespace UtilLoader
{
  void loadFile(std::vector<unsigned char>& buffer, const std::string& filename)
  {
    std::ifstream file(filename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

    //get filesize
    std::streamsize size = 0;
    if(file.seekg(0, std::ios::end).good()) size = file.tellg();
    if(file.seekg(0, std::ios::beg).good()) size -= file.tellg();

    //read contents of the file into the vector
    if(size > 0)
    {
      buffer.resize((size_t)size);
      file.read((char*)(&buffer[0]), size);
    }
    else buffer.clear();
  }
  void loadFile(std::vector<char>& buffer, const std::string& filename)
  {
    std::ifstream file(filename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

    //get filesize
    std::streamsize size = 0;
    if(file.seekg(0, std::ios::end).good()) size = file.tellg();
    if(file.seekg(0, std::ios::beg).good()) size -= file.tellg();

    //read contents of the file into the vector
    if(size > 0)
    {
      buffer.resize((size_t)size);
      file.read((char*)(&buffer[0]), size);
    }
    else buffer.clear();
  }
  

} /* UtilLoader */
