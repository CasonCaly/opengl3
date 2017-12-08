//
//  GLAttribute.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLAttribute.h"

GLAttribute::GLAttribute()
{
    
}

GLAttribute::GLAttribute(GLuint program, GLuint attribute)
{
    m_program = program;
    m_attribute = attribute;
}

void GLAttribute::init(GLuint attribute)
{
    m_attribute = attribute;
}

void GLAttribute::enableVertexAttribArray(){
    glEnableVertexAttribArray(m_attribute);
}

void GLAttribute::disableVertexAttribArray(){
    glDisableVertexAttribArray(m_attribute);
}

void GLAttribute::vertexAttribPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer){
    glVertexAttribPointer(m_attribute, size, type, normalized, stride, pointer);
}

void GLAttribute::vertexAttrib4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    glVertexAttrib4f(m_attribute, x, y, z, w);
}
