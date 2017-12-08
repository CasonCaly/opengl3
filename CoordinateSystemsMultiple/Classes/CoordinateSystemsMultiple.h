#ifndef CoordinateSystemsMultiple_H
#define CoordinateSystemsMultiple_H
#include <vector>
using namespace std;
#include "glclass/GLApp.h"
#include "glclass/GLBuffer.h"
#include "glclass/GLVertexArray.h"
#include "glclass/GLUniform.h"
#include "glclass/GLTexture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CoordinateSystemsMultiple : public GLApp{
    
public:
    
    CoordinateSystemsMultiple();
    
    void init();
    
    void render() override;

private:
    GLVertexArray m_VAO;
    GLBuffer m_VBO;
    
    GLAttribute m_vertexAttr;
    GLAttribute m_texColor;
    
    GLTexture m_texture;
    GLTexture m_texture2;
    
    std::vector<glm::vec3> m_cubePositions;
};
#endif
