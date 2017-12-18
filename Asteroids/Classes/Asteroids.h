#ifndef Asteroids_H
#define Asteroids_H
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

class Asteroids : public GLApp{
    
public:
    
    Asteroids();
    
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
    
    GLBuffer m_buffer;
    
    Camera m_camera;
    GLProgram m_asteroidShader;
    GLProgram m_planetShader;
    
    GLTexture m_cubeTexture;
    GLTexture m_cubemapTexture;

    Model* m_rock;
    Model* m_planet;
    
    glm::mat4* m_modelMatrices;
    int m_amount;
    
private:
    
    float m_deltaTime;
    float m_lastFrame;
    
    float m_lastX;
    float m_lastY;
    
    bool m_firstMouse;
};
#endif
