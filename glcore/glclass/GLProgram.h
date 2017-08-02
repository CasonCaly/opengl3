//
//  GLProgram.hpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLProgram_hpp
#define GLProgram_hpp
#include "GLCore.h"
#include <string>
#include <map>
using namespace std;
#if defined(WIN32)
#include <glew.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif
#include "GLShader.h"
#include "GLUniform.h"
#include "GLAttribute.h"

class GLCORE GLProgram{
    
public:
    
    GLProgram();
    
    void create();
    
    void attachShader(GLuint shader);
    
    void attachShader(GLShader& shader);
    
    void link();
    
    void use();
    
    GLuint getProgram();
    
    std::string getError();
    
    GLUniform* getUniform(const std::string& name);
    
    GLAttribute* getAttribute(const std::string& name);
    
protected:
    
    GLuint m_program;
    
    std::string m_error;
    
    map<string, GLUniform*> m_unifrom;
    
    map<string, GLAttribute*> m_attribute;
};


#endif /* GLShader_hpp */
