//
//  GLAttribute.hpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLAttribute_hpp
#define GLAttribute_hpp
#include "GLCore.h"
#if defined(WIN32)
#include <glew.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif

class GLCORE GLAttribute{
    
public:
    
    GLAttribute();
    
    GLAttribute(GLuint program, GLuint attribute);
    
    void init(GLuint attribute);
    
    void enableVertexAttribArray();
    
    void enableVertexAttribArray(GLuint attribute);
    
    void disableVertexAttribArray();
    
    void vertexAttribPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
    
    void vertexAttrib4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    
protected:
    
    GLuint m_attribute;
    
    GLuint m_program;
};


#endif /* GLAttribute_hpp */
