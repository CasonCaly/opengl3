#include <cmath>
#include "HelloTriangleIndexed.h"


HelloTriangleIndexed::HelloTriangleIndexed()
{
}
 unsigned int VAO;
void HelloTriangleIndexed::init()
{
    
    glEnable(GL_DEPTH_TEST);
    
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    
    m_VBO.gen();
    m_EBO.gen();
    


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    m_EBO.bind(GL_ELEMENT_ARRAY_BUFFER);
    m_EBO.setData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    m_vertexAttr.init(0);//layout (location = 0)
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
}


void HelloTriangleIndexed::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}
