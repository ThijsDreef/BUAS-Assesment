#ifndef SHADERMANAGER__
#define SHADERMANAGER__
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <System/Window/glew.h>


class ShaderManager
{
private:
  std::map<std::string, std::map<std::string, unsigned int>> uniforms;
  std::map<const std::string, unsigned int> shaderlist;
  std::string readShader(const char* fileName);
  unsigned int createShader(GLenum shadertype, std::string source, const char* shaderName);
  std::string textureHandles[16] = {
    "texture0",
    "texture1",
    "texture2",
    "texture3",
    "texture4",
    "texture5",
    "texture6",
    "texture7",
    "texture8",
    "texture9",
    "texture10",
    "texture11",
    "texture12",
    "texture13",
    "texture14",
    "texture15"
  };
public:
  unsigned int getShader(std::string shader);
  void deleteShader(std::string shader);
  unsigned int createShaderProgram(const char* vertex, const char* fragment, std::string shader);
  unsigned int uniformLocation(std::string shader, std::string uniform);
  ShaderManager ();
  virtual ~ShaderManager ();

};
#endif
