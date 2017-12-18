#ifndef InstancingQuads_H
#define InstancingQuads_H
#include <vector>
using namespace std;
#include "glclass/GLApp.h"
#include "glclass/GLBuffer.h"
#include "glclass/GLVertexArray.h"
#include "glclass/GLUniform.h"
#include "glclass/GLTexture.h"
#include "glclass/GLFrameBuffer.h"
#include "glclass/GLRenderBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera/Camera.h"
#include "mesh/Model.h"

class InstancingQuads : public GLApp{
    
public:
    
    InstancingQuads();
    
    void init();
    
    void render() override;

    void initProgram() override;
    
private:
    
    GLVertexArray m_quadVAO;
    GLBuffer m_quadVBO;
    
    GLBuffer m_instanceVBO;
    GLProgram m_shader;
};
#endif
