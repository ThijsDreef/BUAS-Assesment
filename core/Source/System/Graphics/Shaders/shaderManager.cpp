#include "System/Graphics/Shaders/shaderManager.h"

std::string ShaderManager::readShader(const char * fileName)
{
  std::string shaderCode;
  std::ifstream file(fileName, std::ios::in);
  if (!file.good())
  {
    file.close();
    return shaderCode;
  }
  std::string line;
  while (std::getline(file, line))
    shaderCode += line + "\n";
  return shaderCode;
}

unsigned int ShaderManager::createShader(GLenum shaderType, std::string source, const char* shaderName)
{
  int compileResult = 0;
	unsigned int shader = glCreateShader(shaderType);
	const char * shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	//error check time
	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
    std::cout << "error in: " << source << "\n";
    for (unsigned int i = 0; i < shaderLog.size(); i++)
      std::cout << shaderLog[i];
    std::cout << "\n";
		return 0;
	}
	return shader;
}

unsigned int ShaderManager::createShaderProgram(const char* vertex, const char* fragment, std::string shader)
{
  std::string vertexShaderCode = readShader(vertex);
	std::string fragmentShaderCode = readShader(fragment);
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");
	int linkResult = 0;
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> program_log(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &program_log[0]);
		return 0;
	}
  else
  {
    glUseProgram(program);
    std::size_t found;
    std::string code;
    code += vertexShaderCode;
    code += fragmentShaderCode;
    for (unsigned int i = 0; i < 16; i++)
    {
      found = code.find(textureHandles[i]);
      if (found != std::string::npos)
      {
        unsigned int glLocation = glGetUniformLocation(program, textureHandles[i].c_str());
        glUniform1i(glLocation, i);

      }
    }
    found = code.find("\nuniform", 0);
    while (found != std::string::npos)
    {
      std::size_t point = code.find(";", found);
      std::size_t first = code.rfind(" ", point);
      std::string key = code.substr(first + 1, point - first - 1);

      found = code.find("uniform", found + 1);
      unsigned int location = glGetUniformLocation(program, key.c_str());
      uniforms[shader][key] = location;
    }
  }
	shaderlist[shader] = program;
	return program;
}

unsigned int ShaderManager::getShader(std::string shader)
{
  return shaderlist[shader];
}

unsigned int ShaderManager::uniformLocation(std::string shader, std::string uniform)
{
  return uniforms[shader][uniform];
}

void ShaderManager::deleteShader(std::string shader)
{
  unsigned int p = shaderlist[shader];
  glDeleteProgram(p);
  shaderlist.erase(shader);
}

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
  for (auto const &x : shaderlist) {
    unsigned int p = x.second;
    glDeleteProgram(p);

  }
}
