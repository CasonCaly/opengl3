#include <cmath>
#include "CubemapsSkybox.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


CubemapsSkybox::CubemapsSkybox():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void CubemapsSkybox::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };
    
    //skybox vao
    m_skyboxVAO.gen();
    m_skyboxVBO.gen();
    
    m_skyboxVAO.bind();
    
    m_skyboxVBO.bind(GL_ARRAY_BUFFER);
    m_skyboxVBO.setData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    
    GLAttribute verAttr;
    verAttr.init(0);
    verAttr.enableVertexAttribArray();
    verAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    vector<std::string> faces
    {
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/back.jpg",
        "skybox/front.jpg"
    };
    
    m_cubemapTexture.initWithCubemap(faces);
    m_model = new Model("nanosuit/nanosuit.obj");
    
    m_skyboxShader.use();
    m_skyboxShader.setInt("skybox", 0);
}

void CubemapsSkybox::initProgram()
{
    this->createPrograme("Shaders/Skybox.vert", "Shaders/Skybox.frag", m_skyboxShader);
    this->createPrograme("Shaders/Cubemaps.vert", "Shaders/Cubemaps.frag", m_shader);
}

void CubemapsSkybox::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 model(1);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    //draw scene as normal
    m_shader.use();
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
    m_shader.setMat4("model", model);
    m_shader.setMat4("projection", projection);
    m_shader.setMat4("view", view);
    m_shader.setVec3("cameraPos", m_camera.Position);
    //cubes
    m_model->Draw(m_shader);
    
    // draw skybox as last
    glDepthFunc(GL_LEQUAL);
    m_skyboxShader.use();
    view = glm::mat4(glm::mat3(m_camera.GetViewMatrix()));
    m_skyboxShader.setMat4("projection", projection);
    m_skyboxShader.setMat4("view", view);
    // skybox cube
    m_skyboxVAO.bind();
    GLTexture::activeTexture(GL_TEXTURE0);
    m_cubeTexture.bindTexture(GL_TEXTURE_CUBE_MAP);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_skyboxVAO.unbind();
    glDepthFunc(GL_LESS);
}

void CubemapsSkybox::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void CubemapsSkybox::onTouchMove(float x, float y)
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

void CubemapsSkybox::onTouchEnd(float x, float y)
{
    
}

void CubemapsSkybox::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void CubemapsSkybox::onKeyPress(int key, int scancode, int action, int mods)
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

void CubemapsSkybox::initTexture(const std::string& path, GLTexture& tex)
{
    tex.initWithImage(path);
    tex.generateMipmap(GL_TEXTURE_2D);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

