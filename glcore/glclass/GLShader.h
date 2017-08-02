//
//  GLShader.hpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLShader_hpp
#define GLShader_hpp
#include "GLCore.h"
#include <string>
using namespace std;

#if defined(WIN32)
#include <glew.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif

class GLCORE GLShader{
    
public:
    
    GLShader();
    
    void createVertex();
    
    void createFragment();
  
    void create(GLenum type);
    
    void compile(const char* source);
    
    GLuint getShader();
    
    std::string getError();
    
protected:
    
    GLuint m_shader;
    
    std::string m_error;
};


#endif /* GLShader_hpp */
