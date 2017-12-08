#include <cmath>
#include "ShadersInterpolation.h"

ShadersInterpolation::ShadersInterpolation ()
{
}

void ShadersInterpolation ::init()
{
    glEnable(GL_DEPTH_TEST);
    
    float vertices[] = {
        // 位置              // 颜色
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
    
    m_VAO.gen();
    m_VAO.bind();

    m_VBO.gen();
    m_VBO.bind(GL_ARRAY_BUFFER);
    m_VBO.setData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    m_vertexAttr.init(0);//layout (location = 0)
    m_vertexAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    m_vertexAttr.enableVertexAttribArray();
    
    m_colorAttr.init(1);
    m_colorAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    m_colorAttr.enableVertexAttribArray();
    m_VAO.bind();
}


void ShadersInterpolation ::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
