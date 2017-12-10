#include <cmath>
#include "ModelLoading.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


ModelLoading::ModelLoading():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
m_lightPos(1.2f, 1.0f, 2.0f)
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void ModelLoading::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    glEnable(GL_DEPTH_TEST);

    m_model = new Model("nanosuit/nanosuit.obj");
}

void ModelLoading::initProgram()
{
    this->createPrograme("Shaders/ModelLoading.vert", "Shaders/ModelLoading.frag", m_lightingShader);
}

void ModelLoading::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    m_lightingShader.use();
    //view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    m_lightingShader.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    m_lightingShader.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    
    // world transformation
    glm::mat4 model(1);
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
    m_lightingShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
    
    m_model->Draw(m_lightingShader);
    
}

void ModelLoading::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void ModelLoading::onTouchMove(float x, float y)
{
    if (m_firstMouse)
    {
        m_lastX = x;
        m_lastY = y;
        m_firstMouse = false;
    }
    
    float xoffset = x - m_lastX;
    float yoffset = m_lastY - y;
    
    m_lastX = x;
    m_lastY = y;
    
    m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void ModelLoading::onTouchEnd(float x, float y)
{
    
}

void ModelLoading::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void ModelLoading::onKeyPress(int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_W)
    {
        m_camera.ProcessKeyboard(FORWARD, m_deltaTime);
    }
    else if(key == GLFW_KEY_S)
    {
        m_camera.ProcessKeyboard(BACKWARD, m_deltaTime);
    }
    else if(key == GLFW_KEY_A)
    {
        m_camera.ProcessKeyboard(LEFT, m_deltaTime);
    }
    else if(key == GLFW_KEY_D)
    {
        m_camera.ProcessKeyboard(RIGHT, m_deltaTime);
    }
}

