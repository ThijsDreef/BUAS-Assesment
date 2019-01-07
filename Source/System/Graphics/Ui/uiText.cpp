#include "System/Graphics/Ui/uiText.h"

UIText::UIText(std::string startText, Vec2<float> position, Object * object) : Component(object), fontBuffer("font", GL_ARRAY_BUFFER)
{
    text = startText;
    pos = position;
    dirty = true;
    scale = 1.0f;
}

UIText::~UIText()
{
    
}

Matrix<float> & UIText::getMatrix()
{
    Matrix<float> temp;
    temp.translateMatrix(Vec3<float>((shouldCenter) ? centerX * scale : pos[0], pos[1] * inverseAspect, 0));
    // might need to fix this shit
    mv.scaleMatrix(Vec3<float>(scale, scale, 1));
    mv = temp.multiplyByMatrix(mv);
    return mv;
}

std::vector<unsigned int> & UIText::getIndices()
{
    return indices;
}

float UIText::getAlpha()
{
    return alpha;
}

void UIText::buildBuffer(Font * font, float inverseAspect)
{   
    indices.clear();
		
    std::vector<unsigned int> defaultIndices = {0, 1, 2, 0, 3, 1};
    std::vector<TextGPUData> textGPUData;
    Vec2<float> offset;
    unsigned int indiceOffset = 0;
    for (unsigned int j = 0; j < text.size(); j++)
    {
        FontCharacter character = font->getCharacter(text[j]);
        for (unsigned int k = 0; k < character.vertices.size(); k++)
        {
            int kerning = font->getKerning(text[(j + 1 >= 0 ? j + 1 : 0) ], text[j]).amount;
            // float kerning = 0;
            Vec2<float> vt = character.vertices[k].vertexPosition;
            vt = vt + offset;
            
            vt[0] += character.xOffset + kerning;
            vt[1] -= character.yOffset;
            textGPUData.push_back(TextGPUData(vt, character.vertices[k].uvCoords));
        }
        for (unsigned int l = 0; l < defaultIndices.size(); l++)
        {
            indices.push_back(defaultIndices[l] + indiceOffset);
        }
        offset[0] += character.xAdvance;
        indiceOffset += 4;
    }
    this->inverseAspect = inverseAspect;
    Matrix<float> temp;
    centerX = -offset[0] * 0.5;
    temp.translateMatrix(Vec3<float>(pos[0], pos[1] * inverseAspect, 0));
    // might need to fix this shit
    mv.scaleMatrix(Vec3<float>(scale, scale, 1));
    mv = temp.multiplyByMatrix(mv);
    if (textGPUData.size() > 0) fontBuffer.bufferData(sizeof(TextGPUData) * textGPUData.size(), &textGPUData[0], GL_STATIC_DRAW);
}

unsigned int UIText::getBuffer()
{
    return fontBuffer.getBufferId();
}

void UIText::setClean()
{
    dirty = false;
}

void UIText::setText(std::string newText)
{
    text = newText;
    dirty = true;
}

void UIText::setPos(Vec2<float> position)
{
    pos = position;
}

void UIText::setScale(float s)
{
    scale = s;
}

float UIText::getScale()
{
    return scale;
}

bool UIText::isDirty()
{
    return dirty;
}

std::string & UIText::getText()
{
    return text;
}

Vec2<float> & UIText::getPos()
{
    return pos;
}