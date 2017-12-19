//
//  GLUniform.hpp
//  GLUniform
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLUniform_hpp
#define GLUniform_hpp
#include "GLCore.h"
#if defined(WIN32)
#include <glew.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif

class GLCORE GLUniform{
    
public:
    
    GLUniform(GLuint program, GLuint uniform);
    
    void matrix4fv(GLsizei count, GLboolean transpose, const GLfloat *value);
    
	void matrix3fv(GLsizei count, GLboolean transpose, const GLfloat *value);

    void value4f(float v0, float v1, float v2, float v3);
    
	void value3f(float v0, float v1, float v2);

	void value2f(float v0, float v1);

	void value1f(float v0);

	void vector3fv(GLsizei count, const GLfloat *value);

    void value1i(int v0);
    
protected:
    
    GLuint m_unifrom;
    
    GLuint m_program;
};


#endif /* GLUniform_hpp */
