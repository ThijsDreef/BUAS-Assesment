#include "System/Graphics/Ui/font.h"

Font::Font(std::string fontFileName, int padding)
{
    paddingX = padding;
    atlas = new Texture(fontFileName + ".png");
    parseFontFile(fontFileName + ".fnt");
}

Font::~Font() 
{
    delete atlas;
}

FontCharacter & Font::getCharacter(char character)
{
    return characters[character];
}

Kerning & Font::getKerning(char first, char second)
{
    std::string combined;
    combined.append(first, second);
    return kernings[combined];
}

void Font::parseFontFile(std::string fileName)
{
    std::fstream file(fileName);
    std::string line;
    std::cout << fileName;
    if (file.is_open()) 
    {
        while (std::getline(file, line))
        {
            if (line.substr(0, 5) == "char ") {
                parseFontCharacter(line);
            }
            else if (line.substr(0, 8) == "kerning ")
                parseKerning(line);
        }
    }
    setUpCharacters();
}

void Font::parseKerning(std::string & line)
{
    Kerning kerning;
    int first, second;
    sscanf(line.c_str(), "kerning first=%d second=%d amount=%d", &first, &second, &kerning.amount);
    kerning.amount /= atlas->getWidth();
    std::string combined;
    combined.append((char)first, (char)second);
    kernings[combined] = kerning;
}

void Font::parseFontCharacter(std::string & line)
{
    int id, x, y, w, h, xOffset, xAdvance, yOffset;
    FontCharacter character;
    sscanf(line.c_str(), "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d",
    &id, &x, &y, &w, &h, &xOffset, &yOffset, &xAdvance);
    character.x = (float)x;
    character.y = (float)y;
    character.w = (float)w;
    character.h = (float)h;
    character.xOffset = (float)xOffset;
    character.yOffset = (float)yOffset;
    character.xAdvance = (float)xAdvance - paddingX;
    characters[(char)id] = character;
}

void Font::setUpCharacters()
{
    std::vector<FontGPUData> fontBuffer;
    int w = atlas->getWidth();
    int h = atlas->getHeight();
    for (auto & i : characters)
    {
        float normalizedW = i.second.w / w;
        float normalizedH = i.second.h / h;
        float normalizedX = i.second.x / w;
        float normalizedY = i.second.y / h;
        // push quad down by height to make sure it works with the correct baseline
        float normalizedYOffset = -normalizedH;

        i.second.xOffset /= w;
        i.second.yOffset /= h;
        i.second.xAdvance /= w;
        i.second.h /= h;
        i.second.w /= w;
        i.second.x /= w;
        i.second.y /= h;

        i.second.vertices.push_back(FontGPUData(Vec2<float>(normalizedW, normalizedYOffset), Vec2<float>(normalizedX + normalizedW, normalizedY + normalizedH)));
        i.second.vertices.push_back(FontGPUData(Vec2<float>(0, normalizedH + normalizedYOffset), Vec2<float>(normalizedX , normalizedY)));
        i.second.vertices.push_back(FontGPUData(Vec2<float>(0, normalizedYOffset), Vec2<float>(normalizedX, normalizedY + normalizedH)));
        i.second.vertices.push_back(FontGPUData(Vec2<float>(normalizedW, normalizedH + normalizedYOffset), Vec2<float>(normalizedX + normalizedW, normalizedY)));

    }
}

void Font::bindTexture(unsigned int bindingId)
{
    atlas->bind(bindingId);
}
