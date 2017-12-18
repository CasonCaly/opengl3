#ifndef BlendSort_H
#define BlendSort_H
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
#include "camera/Camera.h"
#include "mesh/Model.h"

class BlendSort : public GLApp{
    
public:
    
    BlendSort();
    
    void init();
    
    void render() override;

    void initProgram() override;
    
public:
    
    virtual void onTouchBegan(float x, float y);
    
    virtual void onTouchMove(float x, float y);
    
    virtual void onTouchEnd(float x, float y);
    
    virtual void onMouseScroll(double x, double y);
    
    virtual void onKeyPress(int key, int scancode, int action, int mods) override;
    
    void initTexture(const std::string& path, GLTexture& tex);
    
private:
    GLVertexArray m_cubeVAO;
    GLBuffer m_cubeVBO;
    
    GLVertexArray m_planeVAO;
    GLBuffer m_planeVBO;
    
    GLVertexArray m_transparentVAO;
    GLBuffer m_transparentVBO;
    
    Camera m_camera;
    GLProgram m_shader;
    
    GLTexture m_cubeTexture;
    GLTexture m_floorTexture;
    GLTexture m_transparentTexture;
    
    vector<glm::vec3> m_windows;
private:
    
    float m_deltaTime;
    float m_lastFrame;
    
    float m_lastX;
    float m_lastY;
    
    bool m_firstMouse;
};
#endif
