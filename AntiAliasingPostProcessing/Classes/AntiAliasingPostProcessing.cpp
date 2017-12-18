#include <cmath>
#include "AntiAliasingPostProcessing.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


AntiAliasingPostProcessing::AntiAliasingPostProcessing():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void AntiAliasingPostProcessing::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float cubeVertices[] = {
        // positions
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
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
    verAttr.enableVertexAttribArray(0);
    verAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    verAttr.init(1);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    m_cubeVAO.unbind();
    
    //screen quad vao
    m_quadVAO.gen();
    m_quadVBO.gen();
    
    m_quadVAO.bind();
    m_quadVBO.bind(GL_ARRAY_BUFFER);
    m_quadVBO.setData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    
    verAttr.enableVertexAttribArray(0);
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    verAttr.enableVertexAttribArray(1);
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    //confgigure MSAA framebuffer
    m_framebuffer.gen();
    m_framebuffer.bind();
    //create a multisampled color attachment texture
    m_textureColorBufferMultiSampled.genTextures(GL_TEXTURE_2D_MULTISAMPLE);
    m_textureColorBufferMultiSampled.bindTexture();
    m_textureColorBufferMultiSampled.texImage2DMultisample(4, GL_RGB, m_widthInPixel, m_heightInPixel, GL_TRUE);
    m_textureColorBufferMultiSampled.unbind();
    m_framebuffer.texture2D(m_textureColorBufferMultiSampled);
    
    //create a (also multisampled) renderbuffer object for depth and stencil attachments
    m_rbo.gen();
    m_rbo.bind();
    m_rbo.storageMultisample(4, GL_DEPTH24_STENCIL8, m_widthInPixel, m_heightInPixel);
    m_rbo.unbind();
    m_framebuffer.renderbuffer(m_rbo);
    
    if (m_framebuffer.checkStatusComplete())
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    
    m_framebuffer.unbind();
    
    //configure second post-processing framebuffer
    m_intermediateFBO.gen();
    m_intermediateFBO.bind();
    
    //create a color attacment texture
    m_screenTexture.genTextures(GL_TEXTURE_2D);
    m_screenTexture.bindTexture();
    m_screenTexture.texImage2D( 0, GL_RGB, m_widthInPixel, m_heightInPixel, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    m_screenTexture.texParameteri( GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_screenTexture.texParameteri( GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    m_intermediateFBO.texture2D(m_screenTexture);
    if (m_intermediateFBO.checkStatusComplete())
        cout << "ERROR::FRAMEBUFFER:: Intermediate Framebuffer is not complete!" << endl;
    m_intermediateFBO.unbind();
    
    m_shader.use();
    m_screenShader.setInt("screenTexture", 0);
}

void AntiAliasingPostProcessing::initProgram()
{
    this->createPrograme("Shaders/AntiAliasing.vert", "Shaders/AntiAliasing.frag", m_shader);
    this->createPrograme("Shaders/AAPost.vert", "Shaders/AAPost.frag", m_screenShader);
}

void AntiAliasingPostProcessing::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    //1.draw scene as normal in multisampled buffers
    m_framebuffer.bind();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    //set transformation matrices
    m_shader.use();
    
    glm::mat4 model(1);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    m_shader.setMat4("projection", projection);
    m_shader.setMat4("view", view);
    m_shader.setMat4("model", model);
    
    m_cubeVAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    //2. now blit multisampled buffer(s) to normal colorbuffer of intermedidate FBO. Image is stored in screentexture
    m_framebuffer.bindRead();//set framebuffer as read or src model
    m_intermediateFBO.bindDraw();//set intermidate as draw or dest mode
    glBlitFramebuffer(0, 0, m_widthInPixel, m_heightInPixel, 0, 0, m_widthInPixel, m_heightInPixel, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    
    //3. now render quad with scene's visuals as its texture image
    m_framebuffer.unbind();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    
    //draw screen quad
    m_screenShader.use();
    m_quadVAO.bind();
    GLTexture::activeTexture(GL_TEXTURE0);
    m_screenTexture.bindTexture();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void AntiAliasingPostProcessing::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void AntiAliasingPostProcessing::onTouchMove(float x, float y)
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

void AntiAliasingPostProcessing::onTouchEnd(float x, float y)
{
    
}

void AntiAliasingPostProcessing::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void AntiAliasingPostProcessing::onKeyPress(int key, int scancode, int action, int mods)
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

