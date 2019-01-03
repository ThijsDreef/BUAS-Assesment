#ifndef FONT__
#define FONT__

#include "System/Graphics/Resources/texture.h"
#include "System/Graphics/Resources/buffer.h"
#include <vector>
#include <map>
#include "Math/vec2.h"

struct FontGPUData
{
  Vec2<float> vertexPosition;
  Vec2<float> uvCoords;
  FontGPUData(Vec2<float> vtPos, Vec2<float> uv) 
  {
    vertexPosition = vtPos;
    uvCoords = uv;
  }
};

struct FontCharacter
{
  float xOffset;
  float yOffset;
  float x, y, w, h;
  float xAdvance;
  std::vector<FontGPUData> vertices;
};

struct Kerning 
{
  int amount;
};

class Font 
{
private: 
  int paddingX;
  Texture * atlas;
  std::map<char, FontCharacter> characters;
  std::map<std::string, Kerning> kernings;
  void parseFontFile(std::string fileName);
  void parseKerning(std::string & line);
  void parseFontCharacter(std::string & line);
  void setUpCharacters();
public:
  void bindTexture(unsigned int bindindId);
  Font(std::string fontFileName, int padding);
  virtual ~Font();
  FontCharacter & getCharacter(char character);
  Kerning & getKerning(char first, char second);
};

#endif