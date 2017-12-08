#include <cmath>
#include "Textures.h"
#include "image/GLImage.h"

Textures::Textures()
{
}

void Textures::init()
{
    glEnable(GL_DEPTH_TEST);
    
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();

    //color attribute
    m_vertexColor.init(1);
    m_vertexColor.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    m_vertexColor.enableVertexAttribArray();
    
    //texture attribute
    m_texColor.init(2);
    m_texColor.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    m_texColor.enableVertexAttribArray();
    
    m_texutre.genTextures();
    m_texutre.bindTexture(GL_TEXTURE_2D);
    m_texutre.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_texutre.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_texutre.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_texutre.texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLImage image;
    if(image.initWithImage("container.jpg"))
    {
        m_texutre.texImage2D(GL_TEXTURE_2D, 0, image.getInternalFormat(), image.getWidth(), image.getHeight(), 0, image.getInternalFormat(), GL_UNSIGNED_BYTE, image.getData());
        m_texutre.generateMipmap(GL_TEXTURE_2D);
    }
    
}


void Textures::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    m_texutre.bindTexture(GL_TEXTURE_2D);
    m_VAO.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
