#include <cmath>
#include "StencilTesting.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


StencilTesting::StencilTesting():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void StencilTesting::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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
    
    m_planeVAO.unbind();
    
    m_cubeTexture.initWithImage("marble.png");
    m_cubeTexture.generateMipmap(GL_TEXTURE_2D);
    m_cubeTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_cubeTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_cubeTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    m_cubeTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
    m_floorTexture.initWithImage("metal.jpg");
    m_floorTexture.generateMipmap(GL_TEXTURE_2D);
    m_floorTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_floorTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_floorTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    m_floorTexture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    m_shader.use();
    m_shader.setInt("texture1", 0);
}

void StencilTesting::initProgram()
{
    this->createPrograme("Shaders/StencilTesting.vert", "Shaders/StencilTesting.frag", m_shader);
    this->createPrograme("Shaders/StencilTesting.vert", "Shaders/StencilSingleColor.frag", m_shaderSignleColor);
}

void StencilTesting::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    
    m_shaderSignleColor.use();
    glm::mat4 model(1);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    m_shaderSignleColor.setMat4("projection", projection);
    m_shaderSignleColor.setMat4("view", view);
    
    m_shader.use();
    m_shader.setMat4("projection", projection);
    m_shader.setMat4("view", view);
    
    //draw floor as normal, but don't write the floor to the stencil buffer,we only care about the containers.
    //We set its mask to 0x00 to not write to the stencil buffer.
   // glStencilMask(0x00);
    //floor
    m_planeVAO.bind();
    m_floorTexture.bindTexture(GL_TEXTURE_2D);
    m_shader.setMat4("model", glm::mat4(1));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_planeVAO.unbind();
    // 1st. render pass, draw objects as normal, writing to the stencil buffer
    // --------------------------------------------------------------------
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    // cubes
    m_cubeVAO.bind();
   
    m_cubeTexture.bindTexture(GL_TEXTURE_2D);
    
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    m_shader.setMat4("model", model);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    m_shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    

    // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
    // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing
    // the objects' size differences, making it look like borders.
    //
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    m_shaderSignleColor.use();
    float scale = 1.1;
    
    m_cubeTexture.bindTexture(GL_TEXTURE_2D);
    
    model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    m_shaderSignleColor.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    m_shaderSignleColor.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    m_cubeVAO.unbind();
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
}

void StencilTesting::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void StencilTesting::onTouchMove(float x, float y)
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

void StencilTesting::onTouchEnd(float x, float y)
{
    
}

void StencilTesting::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void StencilTesting::onKeyPress(int key, int scancode, int action, int mods)
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

