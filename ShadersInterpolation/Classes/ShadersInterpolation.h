#ifndef ShadersInterpolation_H
#define ShadersInterpolation_H
#include <vector>
using namespace std;
#include "glclass/GLApp.h"
#include "glclass/GLBuffer.h"
#include "glclass/GLVertexArray.h"
#include "glclass/GLUniform.h"

class ShadersInterpolation : public GLApp{
    
public:
    
    ShadersInterpolation();
    
    void init();
    
    void render() override;

private:
    GLVertexArray m_VAO;
    GLBuffer m_VBO;
    
    GLAttribute m_vertexAttr;
    GLAttribute m_colorAttr;
};
#endif
