//
//  GLUniform.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLUniform.h"

GLUniform::GLUniform(GLuint program, GLuint uniform){
    m_program = program;
    m_unifrom = uniform;
}

void GLUniform::matrix4fv(GLsizei count, GLboolean transpose, const GLfloat *value){
    glUniformMatrix4fv(m_unifrom, count, transpose, value);
}

void GLUniform::matrix3fv(GLsizei count, GLboolean transpose, const GLfloat *value){
	glUniformMatrix3fv(m_unifrom, count, transpose, value);
}

void GLUniform::value4f(float v0, float v1, float v2, float v3)
{
    glUniform4f(m_unifrom, v0, v1, v2, v3);
}

void GLUniform::value3f(float v0, float v1, float v2)
{
	glUniform3f(m_unifrom, v0, v1, v2);
}

void GLUniform::value2f(float v0, float v1)
{
	glUniform2f(m_unifrom, v0, v1);
}

void GLUniform::value1f(float v0)
{
	glUniform1f(m_unifrom, v0);
}

void GLUniform::vector3fv(GLsizei count, const GLfloat *value)
{
	glUniform3fv(m_unifrom, count, value);
}

void GLUniform::value1i(int v0)
{
    glUniform1i(m_unifrom, v0);
}
