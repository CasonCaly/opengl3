#ifndef AntiAliasingPostProcessing_H
#define AntiAliasingPostProcessing_H
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

class BlinnPhong : public GLApp{
    
public:
    
    BlinnPhong();
    
    void init();
    
    void render() override;

    void initProgram() override;
    
public:
    
    virtual void onTouchBegan(float x, float y);
    
    virtual void onTouchMove(float x, float y);
    
    virtual void onTouchEnd(float x, float y);
    
    virtual void onMouseScroll(double x, double y);
    
    virtual void onKeyPress(int key, int scancode, int action, int mods) override;
    
private:
    GLVertexArray m_planeVAO;
    GLBuffer m_planeVBO;

    
    Camera m_camera;
    GLProgram m_shader;
    
    glm::vec3 m_lightPos;
    bool m_blinn;
    
    GLTexture m_floorTexture;
    
private:
    
    float m_deltaTime;
    float m_lastFrame;
    
    float m_lastX;
    float m_lastY;
    
    bool m_firstMouse;
};
#endif
