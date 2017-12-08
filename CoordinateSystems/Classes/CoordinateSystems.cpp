#include <cmath>
#include "CoordinateSystems.h"
#include "image/GLImage.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CoordinateSystems::CoordinateSystems()
{
}

void CoordinateSystems::init()
{
    glEnable(GL_DEPTH_TEST);
    
    float vertices[] = {
        // positions        // texture coords
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    m_VBO.gen();
    m_EBO.gen();
    
    m_VAO.gen();
    m_VAO.bind();

    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    m_EBO.bind(GL_ELEMENT_ARRAY_BUFFER);
    m_EBO.setData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
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


void CoordinateSystems::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    GLTexture::activeTexture(GL_TEXTURE0);
    m_texture.bindTexture(GL_TEXTURE_2D);
    
    GLTexture::activeTexture(GL_TEXTURE1);
    m_texture2.bindTexture(GL_TEXTURE_2D);
    
    glm::mat4 model(1);
    glm::mat4 view(1);
    glm::mat4 projection(1);
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    
    m_glProgram.getUniform("model")->matrix4fv(1, GL_FALSE, glm::value_ptr(model));
    m_glProgram.getUniform("view")->matrix4fv(1, GL_FALSE, glm::value_ptr(view));
    m_glProgram.getUniform("projection")->matrix4fv(1, GL_FALSE, glm::value_ptr(projection));
    
    m_VAO.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
