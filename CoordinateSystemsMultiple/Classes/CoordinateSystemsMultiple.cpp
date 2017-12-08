#include <cmath>
#include "CoordinateSystemsMultiple.h"
#include "image/GLImage.h"


CoordinateSystemsMultiple::CoordinateSystemsMultiple()
{
}

void CoordinateSystemsMultiple::init()
{
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f
    };
    
    m_cubePositions.push_back(glm::vec3( 0.0f,  0.0f,  0.0f));
    m_cubePositions.push_back(glm::vec3( 2.0f,  5.0f, -15.0f));
    m_cubePositions.push_back(glm::vec3(-1.5f, -2.2f, -2.5f));
    m_cubePositions.push_back(glm::vec3(-3.8f, -2.0f, -12.3f));
    m_cubePositions.push_back(glm::vec3( 2.4f, -0.4f, -3.5f));
    m_cubePositions.push_back(glm::vec3(-1.7f,  3.0f, -7.5f));
    m_cubePositions.push_back(glm::vec3( 1.3f, -2.0f, -2.5f));
    m_cubePositions.push_back(glm::vec3( 1.5f,  2.0f, -2.5f));
    m_cubePositions.push_back(glm::vec3( 1.5f,  0.2f, -1.5f));
    m_cubePositions.push_back(glm::vec3(-1.3f,  1.0f, -1.5f));
    
    m_VAO.gen();
    m_VAO.bind();

    m_VBO.gen();
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //position attribute
    m_vertexAttr.init(0);//layout (location = 0)
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();
    
    //texture attribute
    m_texColor.init(1);
    m_texColor.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    m_texColor.enableVertexAttribArray();
    
    m_texture.genTextures();
    m_texture.bindTexture(GL_TEXTURE_2D);
    m_texture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_texture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_texture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_texture.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLImage image;
    if(image.initWithImage("container.jpg"))
    {
        m_texture.texImage2D(GL_TEXTURE_2D, 0, image.getInternalFormat(), image.getWidth(), image.getHeight(), 0, image.getInternalFormat(), GL_UNSIGNED_BYTE, image.getData());
    }
    
    m_texture2.genTextures();
    m_texture2.bindTexture(GL_TEXTURE_2D);
    m_texture2.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_texture2.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_texture2.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_texture2.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLImage image2;
    if(image2.initWithImage("awesomeface.png"))
    {
        m_texture2.texImage2D(GL_TEXTURE_2D, 0, image2.getInternalFormat(), image2.getWidth(), image2.getHeight(), 0, image2.getInternalFormat(), GL_UNSIGNED_BYTE, image2.getData());
    }
    
    GLUniform* texUni1 = m_glProgram.getUniform("texture1");
    texUni1->value1i(0);
    GLUniform* texUni2 = m_glProgram.getUniform("texture2");
    texUni2->value1i(1);
}


void CoordinateSystemsMultiple::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    GLTexture::activeTexture(GL_TEXTURE0);
    m_texture.bindTexture(GL_TEXTURE_2D);
    
    GLTexture::activeTexture(GL_TEXTURE1);
    m_texture2.bindTexture(GL_TEXTURE_2D);
    
    glm::mat4 model(1);
    glm::mat4 view(1);
    glm::mat4 projection(1);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    
    
    m_glProgram.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    m_glProgram.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    
    m_VAO.bind();
    for(int i = 0; i < m_cubePositions.size(); i++)
    {
        glm::mat4 model;
        model = glm::translate(model, m_cubePositions[i]);
        float angle = 20.0f * i;
        if(i % 3 == 0)
            angle = 20.0f * i + (float)glfwGetTime();
        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        
        m_glProgram.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
}
