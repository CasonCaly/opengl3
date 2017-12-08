#ifndef CameraMouseZoom_H
#define CameraMouseZoom_H
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

class CameraMouseZoom : public GLApp{
    
public:
    
    CameraMouseZoom();
    
    void init();
    
    void render() override;

    virtual void onTouchBegan(float x, float y);
    
    virtual void onTouchMove(float x, float y);
    
    virtual void onTouchEnd(float x, float y);
    
    virtual void onMouseScroll(double x, double y);
    
    virtual void onKeyPress(int key, int scancode, int action, int mods) override;
    
private:
    GLVertexArray m_VAO;
    GLBuffer m_VBO;
    
    GLAttribute m_vertexAttr;
    GLAttribute m_texColor;
    
    GLTexture m_texture;
    GLTexture m_texture2;
    
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;
    
    float m_yaw;
    float m_pitch;
    
    float m_lastX;
    float m_lastY;
    float m_fov;
    
    bool m_firstMouse;
    
    float m_deltaTime;
    float m_lastFrame;
    
    std::vector<glm::vec3> m_cubePositions;
};
#endif
