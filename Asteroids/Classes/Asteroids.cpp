#include <cmath>
#include "Asteroids.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


Asteroids::Asteroids():
m_camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    m_deltaTime = 0.0f;
    m_lastFrame = 0.0f;
    m_firstMouse = true;
}

void Asteroids::init()
{
    m_lastX = m_width/2;
    m_lastY = m_height/2;
    
    glEnable(GL_DEPTH_TEST);
    
    
    m_rock = new Model("rock/rock.obj");
    m_planet = new Model("planet/planet.obj");
    
    m_amount = 100000/2;
    
    m_modelMatrices = new glm::mat4[m_amount];
    srand(glfwGetTime());
    float radius = 150.0f;
    float offset = 25.0f;
    for(int i = 0; i < m_amount; i++)
    {
        glm::mat4 model(1);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)m_amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));
        
        // 2. scale: Scale between 0.05 and 0.25f
        float scale = (rand() % 20) / 100.0f + 0.05;
        model = glm::scale(model, glm::vec3(scale));
        
        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
        
        // 4. now add to list of matrices
        m_modelMatrices[i] = model;
    }
    m_camera.MovementSpeed = 10;
    m_camera.Position = glm::vec3(1.98133e-06, 0, 48.3275);
    
    m_buffer.gen();
    m_buffer.bind(GL_ARRAY_BUFFER);
    m_buffer.setData(GL_ARRAY_BUFFER, m_amount * sizeof(glm::mat4), &m_modelMatrices[0], GL_STATIC_DRAW);
    
    //set transformation marices as an instance vertex attribute (with divisor 1)
    GLAttribute attr;
    for(int i = 0; i < m_rock->meshes.size(); i++)
    {
        int VAO = m_rock->meshes[i].VAO;
        glBindVertexArray(VAO);
        attr.enableVertexAttribArray(3);
        attr.vertexAttribPointer(4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        
        attr.enableVertexAttribArray(4);
        attr.vertexAttribPointer(4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        
        attr.enableVertexAttribArray(5);
        attr.vertexAttribPointer(4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        
        attr.enableVertexAttribArray(6);
        attr.vertexAttribPointer(4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
        //tell opengl the matrices is a instance array
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        
        glBindVertexArray(0);
    }
}

void Asteroids::initProgram()
{
    this->createPrograme("Shaders/Asteroids.vert", "Shaders/Asteroids.frag", m_asteroidShader);
    this->createPrograme("Shaders/Planet.vert", "Shaders/Planet.frag", m_planetShader);
}

void Asteroids::render()
{
    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)m_width / (float)m_height, 0.1f, 1000.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    
    m_asteroidShader.use();
    m_asteroidShader.setMat4("projection", projection);
    m_asteroidShader.setMat4("view", view);
    
    m_planetShader.use();
    m_planetShader.setMat4("projection", projection);
    m_planetShader.setMat4("view", view);
    
    //draw planet
    glm::mat4 model(1);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    m_planetShader.setMat4("model", model);
    m_planet->Draw(m_planetShader);
    
    //draw meteorites
    m_asteroidShader.use();
    m_asteroidShader.setInt("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_rock->textures_loaded[0].id);
    
    for(int i = 0; i < m_rock->meshes.size(); i++)
    {
        glBindVertexArray(m_rock->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, m_rock->meshes[i].indices.size(), GL_UNSIGNED_INT, 0, m_amount);
        glBindVertexArray(0);
    }
}

void Asteroids::onTouchBegan(float x, float y)
{
    m_lastX = x;
    m_lastY = y;
}

void Asteroids::onTouchMove(float x, float y)
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

void Asteroids::onTouchEnd(float x, float y)
{
    
}

void Asteroids::onMouseScroll(double x, double y)
{
    m_camera.ProcessMouseScroll(y);
}

void Asteroids::onKeyPress(int key, int scancode, int action, int mods)
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
    
    glm::vec3 pos = m_camera.Position;
    cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<endl;
}

void Asteroids::initTexture(const std::string& path, GLTexture& tex)
{
    tex.initWithImage(path);
    tex.generateMipmap(GL_TEXTURE_2D);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

