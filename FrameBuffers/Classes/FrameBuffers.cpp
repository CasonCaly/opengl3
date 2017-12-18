#include <cmath>
#include "FrameBuffers.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


FrameBuffers::FrameBuffers():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void FrameBuffers::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        
        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
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
    
    //screen quad vao
    m_quadVAO.gen();
    m_quadVBO.gen();
    
    m_quadVAO.bind();
    m_quadVBO.bind(GL_ARRAY_BUFFER);
    m_quadVBO.setData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    
    verAttr.init(0);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    verAttr.init(1);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    // load textures
    this->initTexture("metal.jpg", m_cubeTexture);
    this->initTexture("metal.jpg", m_floorTexture);
    
    m_shader.use();
    m_shader.setInt("texture1", 0);
    
    m_screenShader.use();
    m_screenShader.setInt("screenTexture", 0);
    
    m_framebuffer.gen();
    m_framebuffer.bind();
    
    m_textureColorbuffer.genTextures();
    m_textureColorbuffer.bindTexture(GL_TEXTURE_2D);
    m_textureColorbuffer.texImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_widthInPixel, m_heightInPixel, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    m_textureColorbuffer.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_textureColorbuffer.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    m_framebuffer.texture2D(m_textureColorbuffer);
    
    m_rbo.gen();
    m_rbo.bind();
    m_rbo.renderbufferStorage(GL_DEPTH24_STENCIL8, m_widthInPixel, m_heightInPixel);
    
    m_framebuffer.renderbuffer(m_rbo);
    
    if (m_framebuffer.checkStatusComplete())
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    
    m_framebuffer.unbind();
}

void FrameBuffers::initProgram()
{
    this->createPrograme("Shaders/FrameBuffers.vert", "Shaders/FrameBuffers.frag", m_shader);
    this->createPrograme("Shaders/FrameBuffersScreen.vert", "Shaders/FrameBuffersScreen.frag", m_screenShader);
}

void FrameBuffers::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    
    m_framebuffer.bind();
    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 model(1);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
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
    m_planeVAO.unbind();
//
    m_framebuffer.unbind();
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

    m_screenShader.use();
    m_quadVAO.bind();
    m_textureColorbuffer.bindTexture(GL_TEXTURE_2D);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FrameBuffers::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void FrameBuffers::onTouchMove(float x, float y)
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

void FrameBuffers::onTouchEnd(float x, float y)
{
    
}

void FrameBuffers::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void FrameBuffers::onKeyPress(int key, int scancode, int action, int mods)
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

void FrameBuffers::initTexture(const std::string& path, GLTexture& tex)
{
    tex.initWithImage(path);
    tex.generateMipmap(GL_TEXTURE_2D);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

