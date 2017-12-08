#ifndef Textures_H
#define Textures_H
#include <vector>
using namespace std;
#include "glclass/GLApp.h"
#include "glclass/GLBuffer.h"
#include "glclass/GLVertexArray.h"
#include "glclass/GLUniform.h"
#include "glclass/GLTexture.h"

class Textures : public GLApp{
    
public:
    
    Textures();
    
    void init();
    
    void render() override;

private:
    GLVertexArray m_VAO;
    GLBuffer m_VBO;
    GLBuffer m_EBO;
    
    GLAttribute m_vertexAttr;
    GLAttribute m_vertexColor;
    GLAttribute m_texColor;
    
    GLTexture m_texutre;
};
#endif
