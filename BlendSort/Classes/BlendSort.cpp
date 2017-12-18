#include <cmath>
#include "BlendSort.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


BlendSort::BlendSort():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void BlendSort::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_STENCIL_TEST);
//    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    
    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };
    
    //cube vao
    m_cubeVAO.gen();
    m_cubeVBO.gen();
    
    m_cubeVAO.bind();
    m_cubeVBO.bind(GL_ARRAY_BUFFER);
    m_cubeVBO.setData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    
    GLAttribute verAttr;
    verAttr.init(0);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    verAttr.init(1);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    m_cubeVAO.unbind();
    
    //plane vao
    m_planeVAO.gen();
    m_planeVBO.gen();
    
    m_planeVAO.bind();
    
    m_planeVBO.bind(GL_ARRAY_BUFFER);
    m_planeVBO.setData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    
    verAttr.init(0);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    verAttr.init(1);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    //transparent vao
    m_transparentVAO.gen();
    m_transparentVBO.gen();
    
    m_transparentVAO.bind();
    m_transparentVBO.bind(GL_ARRAY_BUFFER);
    m_transparentVBO.setData(GL_ARRAY_BUFFER, sizeof(transparentVertices), &transparentVertices, GL_STATIC_DRAW);
    
    verAttr.init(0);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    verAttr.init(1);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    // load textures
    this->initTexture("marble.png", m_cubeTexture);
    this->initTexture("metal.jpg", m_floorTexture);
    this->initTexture("window.png", m_transparentTexture);
    
    m_windows.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
    m_windows.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
    m_windows.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
    m_windows.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
    m_windows.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
    
    m_shader.use();
    m_shader.setInt("texture1", 0);
}

void BlendSort::initProgram()
{
    this->createPrograme("Shaders/Blending.vert", "Shaders/Blending.frag", m_shader);
}

void BlendSort::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 model(1);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    // sort the transparent windows before rendering
    // ---------------------------------------------
    std::map<float, glm::vec3> sorted;
    for (unsigned int i = 0; i < m_windows.size(); i++)
    {
        float distance = glm::length(m_camera.Position - m_windows[i]);
        sorted[distance] = m_windows[i];
    }
    
    //draw objects
    m_shader.use();
    m_shader.setMat4("projection", projection);
    m_shader.setMat4("view", view);
    
    //cubes
    m_cubeVAO.bind();
    GLTexture::activeTexture(GL_TEXTURE0);
    m_cubeTexture.bindTexture(GL_TEXTURE_2D);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    m_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    m_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    //floor
    m_planeVAO.bind();
    m_floorTexture.bindTexture(GL_TEXTURE_2D);
    model = glm::mat4();
    m_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    //windows (from furthest to nearest)
    m_transparentVAO.bind();
    m_transparentTexture.bindTexture(GL_TEXTURE_2D);
    
//    for(int i = 0; i < m_windows.size(); i++)
//    {
//        model = glm::mat4();
//        model = glm::translate(model, m_windows[i]);
//        m_shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//    }
    for(auto begin = sorted.rbegin(); begin != sorted.rend(); begin++)
    {
        model = glm::mat4();
        model = glm::translate(model, begin->second);
        m_shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void BlendSort::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void BlendSort::onTouchMove(float x, float y)
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

void BlendSort::onTouchEnd(float x, float y)
{
    
}

void BlendSort::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void BlendSort::onKeyPress(int key, int scancode, int action, int mods)
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

void BlendSort::initTexture(const std::string& path, GLTexture& tex)
{
    tex.initWithImage(path);
    tex.generateMipmap(GL_TEXTURE_2D);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

