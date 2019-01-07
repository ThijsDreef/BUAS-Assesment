#include "System/Graphics/Ui/uiRenderer.h"

UiRenderer::UiRenderer(std::string fontFileName, ShaderManager * shader, unsigned int width, unsigned int height, int padding) : font(fontFileName, padding)
{
    shaderManager = shader;
    shader->createShaderProgram("shaders/font/font.vert", "shaders/font/font.frag", "font");
    shader->createShaderProgram("shaders/font/font.vert", "shaders/font/fontOutline.frag", "outLine");
    w = width;
    h = height;
    setupFormat();

}

UiRenderer::~UiRenderer()
{
    glDeleteVertexArrays(1, &vao);
}

void UiRenderer::setupFormat()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribFormat(0, 2, GL_FLOAT, false,  0); // position
    glVertexAttribBinding(0, 0); // position -> stream 0
    glEnableVertexAttribArray(1);
    glVertexAttribFormat(1, 2, GL_FLOAT, false, 8); // uv
    glVertexAttribBinding(1, 0); 
}

void UiRenderer::renderText()
{
    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(vao);
    font.bindTexture(10);
    for (unsigned int i = 0; i < textObjects.size(); i++)
    {
        glUseProgram(shaderManager->getShader((textObjects[i]->outLine) ? "outLine" : "font"));
        if (textObjects[i]->isDead())
        {
            textObjects[i]->setRemoved();
            textObjects.erase(textObjects.begin() + i);
        }
        else if (textObjects[i]->isDirty()) 
        {
            textObjects[i]->buildBuffer(&font, (float)w/h);
            textObjects[i]->setClean();
        } 

        glBindVertexBuffer(0, textObjects[i]->getBuffer(), 0, 16);
        std::vector<unsigned int> indices = textObjects[i]->getIndices();
        Matrix<float> mvp;
        mvp.orthographicView(1, (float)w / h, -10, 10);
        mvp = mvp.multiplyByMatrix(textObjects[i]->getMatrix());
        glUniformMatrix4fv(shaderManager->uniformLocation("font", "mvp"), 1, false, &mvp.matrix[0]);
        glUniform1f(shaderManager->uniformLocation("font", "uAlpha"), textObjects[i]->getAlpha());

        if (indices.size() > 0) glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);

    }
    glDisable(GL_BLEND);
}

void UiRenderer::update()
{
    renderText();
}

void UiRenderer::addObject(Object * object)
{
    UIText * text = object->getComponent<UIText>();
    if (text) textObjects.push_back(text);
}
