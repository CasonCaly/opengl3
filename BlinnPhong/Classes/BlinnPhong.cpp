#include <cmath>
#include "BlinnPhong.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


BlinnPhong::BlinnPhong():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
m_lightPos(0.0f, 0.0f, 0.0f)
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
    m_blinn = false;
}

void BlinnPhong::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    GLfloat planeVertices[] = {
        // Positions          // Normals         // Texture Coords
        8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
        -8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
        
        8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
        -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
        8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
    };
    
    //cube vao
    m_planeVAO.gen();
    m_planeVBO.gen();
    
    m_planeVAO.bind();
    
    m_planeVBO.bind(GL_ARRAY_BUFFER);
    m_planeVBO.setData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    
    GLAttribute attr;
    attr.enableVertexAttribArray(0);
    attr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    
    attr.enableVertexAttribArray(1);
    attr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    
    attr.enableVertexAttribArray(2);
    attr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    
    m_planeVAO.unbind();
    
    m_shader.use();
    m_floorTexture.initWithImage("wood.png");
}

void BlinnPhong::initProgram()
{
    this->createPrograme("Shaders/AdvancedLighting.vert", "Shaders/AdvancedLighting.frag", m_shader);
}

void BlinnPhong::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    m_shader.use();
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(m_camera.Zoom, (float)m_width / (float)m_height, 0.1f, 100.0f);
    
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    //set light unifroms
    m_shader.setVec3("lightPos", m_lightPos);
    m_shader.setVec3("viewPos", m_camera.Position);
    m_shader.setInt("blinn", m_blinn);
    //floor
    m_planeVAO.bind();
    m_floorTexture.bindTexture();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_planeVAO.unbind();
}

void BlinnPhong::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void BlinnPhong::onTouchMove(float x, float y)
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

void BlinnPhong::onTouchEnd(float x, float y)
{
    
}

void BlinnPhong::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void BlinnPhong::onKeyPress(int key, int scancode, int action, int mods)
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
    else if(key == GLFW_KEY_B)
    {
        if(GLFW_RELEASE == action)
        {
            m_blinn = !m_blinn;
        }
    }
}

