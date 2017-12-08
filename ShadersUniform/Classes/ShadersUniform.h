#ifndef ShadersUniform_H
#define ShadersUniform_H
#include <vector>
using namespace std;
#include "glclass/GLApp.h"
#include "glclass/GLBuffer.h"
#include "glclass/GLVertexArray.h"
#include "glclass/GLUniform.h"

class ShadersUniform : public GLApp{
    
public:
    
    ShadersUniform();
    
    void init();
    
    void render() override;

private:
    GLVertexArray m_VAO;
    GLBuffer m_VBO;
    
    GLAttribute m_vertexAttr;
    GLUniform* m_vertexColor;
};
#endif
