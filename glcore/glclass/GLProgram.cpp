//
//  GLProgram.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLProgram.h"
#include <iostream>

GLProgram::GLProgram(){
    m_program = -1;
}


void GLProgram::create(){
    m_program = glCreateProgram();
}

void GLProgram::attachShader(GLuint shader){
    glAttachShader(m_program, shader);
}

void GLProgram::attachShader(GLShader& shader){
    glAttachShader(m_program, shader.getShader());
}

void GLProgram::link(){
    glLinkProgram(m_program);
    
    GLint linkSuccess;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[8192];
        glGetProgramInfoLog(m_program, sizeof(messages), 0, &messages[0]);
        m_error.append(messages);
        std::cout<<m_error<<endl;
    }
}

void GLProgram::use(){
    glUseProgram(m_program);
}

GLuint GLProgram::getProgram(){
    return m_program;
}

std::string GLProgram::getError(){
    return m_error;
}

GLUniform* GLProgram::getUniform(const std::string& name){
    auto target = m_unifrom.find(name);
    if(target != m_unifrom.end())
        return target->second;
    
    GLint uniform = glGetUniformLocation(m_program, name.c_str());
    GLUniform* glUnifrom = new GLUniform(m_program, uniform);
    m_unifrom.insert(make_pair(name, glUnifrom));
    return glUnifrom;
}

GLAttribute* GLProgram::getAttribute(const std::string& name){
    auto target = m_attribute.find(name);
    if(target != m_attribute.end())
        return target->second;
    
    GLint attribute = glGetAttribLocation(m_program, name.c_str());
    GLAttribute* glAttribute = new GLAttribute(m_program, attribute);
    m_attribute.insert(make_pair(name, glAttribute));
    return glAttribute;
}

void GLProgram::setInt(const std::string& name, int value)
{
    GLUniform* uniform = this->getUniform(name);
    if(uniform)
        uniform->value1i(value);
}

void GLProgram::setMat4(const std::string& name, const glm::mat4& value)
{
    GLUniform* uniform = this->getUniform(name);
    if(uniform)
        uniform->matrix4fv(1, GL_FALSE, glm::value_ptr(value));
}

void GLProgram::setVec3(const std::string& name, const glm::vec3& value)
{
    GLUniform* uniform = this->getUniform(name);
    if(uniform)
        uniform->vector3fv(1, glm::value_ptr(value));
}

