#ifndef CoordinateSystems_H
#define CoordinateSystems_H
#include <vector>
using namespace std;
#include "glclass/GLApp.h"
#include "glclass/GLBuffer.h"
#include "glclass/GLVertexArray.h"
#include "glclass/GLUniform.h"
#include "glclass/GLTexture.h"

class CoordinateSystems : public GLApp{
    
public:
    
    CoordinateSystems();
    
    void init();
    
    void render() override;

private:
    GLVertexArray m_VAO;
    GLBuffer m_VBO;
    
    GLAttribute m_vertexAttr;
    GLAttribute m_texColor;
    
    GLTexture m_texture;
    GLTexture m_texture2;
};
#endif
