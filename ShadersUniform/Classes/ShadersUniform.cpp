#include <cmath>
#include "ShadersUniform.h"

ShadersUniform::ShadersUniform()
{
}

void ShadersUniform::init()
{
    glEnable(GL_DEPTH_TEST);
    
    float vertices[] = {
        0.5f, -0.5f, 0.0f,  // top right
       -0.5f, -0.5f, 0.0f,  // bottom right
        0.0f,  0.5f, 0.0f
    };
    
    m_VBO.gen();
    
    m_VAO.gen();
    m_VAO.bind();

    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    m_vertexAttr.init(0);//layout (location = 0)
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();

    m_vertexColor = m_glProgram.getUniform("outColor");
    m_VAO.bind();
}


void ShadersUniform::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    float timeValue = (float)glfwGetTime();
    float greenValue = sin(timeValue)/2.0f + 0.5f;
    m_vertexColor->value4f(0.0f, greenValue, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
