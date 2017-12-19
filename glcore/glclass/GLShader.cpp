//
//  GLShader.cpp
//  GLShader
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLShader.h"
#include <iostream>

GLShader::GLShader(){
    m_shader = -1;
}

void GLShader::createVertex(){
    m_shader = glCreateShader(GL_VERTEX_SHADER);
}

void GLShader::createFragment(){
    m_shader = glCreateShader(GL_FRAGMENT_SHADER);
}

void GLShader::create(GLenum type){
    m_shader = glCreateShader(type);
}

void GLShader::compile(const char* source){
    glShaderSource(m_shader, 1, &source, 0);
    glCompileShader(m_shader);
    
    GLint compileSuccess;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar messages[8192];
        glGetShaderInfoLog(m_shader, sizeof(messages), 0, &messages[0]);
        m_error.append(messages);
        std::cout<<m_error<<endl;
    }
}

GLuint GLShader::getShader(){
    return m_shader;
}

std::string GLShader::getError(){
    return m_error;
}
