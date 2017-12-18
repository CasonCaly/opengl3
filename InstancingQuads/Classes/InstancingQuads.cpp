#include <cmath>
#include "InstancingQuads.h"
#include "image/GLImage.h"
#include "glclass/GLTexture.h"


InstancingQuads::InstancingQuads()
{
}

void InstancingQuads::init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // generate a list of 100 quad locations/translation-vectors
    // ---------------------------------------------------------
    glm::vec2 translations[100];
    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    m_instanceVBO.gen();
    m_instanceVBO.bind(GL_ARRAY_BUFFER);
    m_instanceVBO.setData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
    m_instanceVBO.unbind();
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float quadVertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
        
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };
    
    m_quadVAO.gen();
    m_quadVBO.gen();
    
    m_quadVAO.bind();
    m_quadVBO.bind(GL_ARRAY_BUFFER);
    m_quadVBO.setData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    
    GLAttribute verAttr;
    verAttr.enableVertexAttribArray(0);
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    verAttr.enableVertexAttribArray(1);
    verAttr.vertexAttribPointer(3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    
    // also set instance data
    verAttr.enableVertexAttribArray(2);
    m_instanceVBO.bind(GL_ARRAY_BUFFER);
    verAttr.vertexAttribPointer(2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    m_instanceVBO.unbind();
    glVertexAttribDivisor(2, 1);
}

void InstancingQuads::initProgram()
{
    this->createPrograme("Shaders/InstancingQuads.vert", "Shaders/InstancingQuads.frag", m_shader);
}

void InstancingQuads::render()
{    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    m_shader.use();
    m_quadVAO.bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
    m_quadVAO.unbind();
}


