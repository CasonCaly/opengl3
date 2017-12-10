#include <cmath>
#include "LightingMapsDiffuse.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"

LightingMapsDiffuse::LightingMapsDiffuse():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f)),
m_lightPos(1.2f, 1.0f, 2.0f)
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void LightingMapsDiffuse::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    
    m_cubeVAO.gen();

    m_VBO.gen();
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    m_cubeVAO.bind();
    //position attribute
    m_vertexAttr.init(0);//layout (location = 0)
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();
    //normal attribute
    m_normalAttr.init(1);
    m_normalAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    m_normalAttr.enableVertexAttribArray();
    //texture attribute
    m_texAttr.init(2);
    m_texAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    m_texAttr.enableVertexAttribArray();
    
    m_ligthVAO.gen();
    m_ligthVAO.bind();
    
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();

    GLTexture diffuseMap;
    diffuseMap.initWithImage("container2.png");
    m_lightingShader.use();
    m_lightingShader.getUniform("material.diffuse")->value1i(0);
}

void LightingMapsDiffuse::initProgram()
{
    this->createPrograme("Shaders/LightingMaps.vert", "Shaders/LightingMaps.frag", m_lightingShader);
    this->createPrograme("Shaders/Lamp.vert", "Shaders/Lamp.frag", m_lampShader);
}

void LightingMapsDiffuse::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    //light
    m_lightingShader.use();
    m_lightingShader.getUniform("light.position")->vector3fv(1, &m_lightPos[0]);
    m_lightingShader.getUniform("viewPos")->vector3fv(1, &m_camera.Position[0]);
    
    //light properties
    m_lightingShader.getUniform("light.ambient")->value3f(0.2f, 0.2f, 0.2f);
    m_lightingShader.getUniform("light.diffuse")->value3f(0.5f, 0.5f, 0.5f);
    m_lightingShader.getUniform("light.specular")->value3f(1.0f, 1.0f, 1.0f);
    
    //material properties
    m_lightingShader.getUniform("material.specular")->value3f(0.5f, 0.5f, 0.5f);
    m_lightingShader.getUniform("material.shininess")->value1f(64.0f);
    
    //view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    m_lightingShader.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    m_lightingShader.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    
    // world transformation
    glm::mat4 model;
    m_lightingShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
    
    //reander the cube
    m_cubeVAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    //lamp
    m_lampShader.use();
    m_lampShader.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    m_lampShader.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    
    model = glm::mat4();
    model = glm::translate(model, m_lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cub
    m_lampShader.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
    
    m_ligthVAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightingMapsDiffuse::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void LightingMapsDiffuse::onTouchMove(float x, float y)
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

void LightingMapsDiffuse::onTouchEnd(float x, float y)
{
    
}

void LightingMapsDiffuse::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void LightingMapsDiffuse::onKeyPress(int key, int scancode, int action, int mods)
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

