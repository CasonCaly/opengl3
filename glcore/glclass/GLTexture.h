#ifndef GL_Texture_h
#define GL_Texture_h
#include "GLCore.h"
#if defined(WIN32)
#include <glew.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif
#include <string>

class GLCORE GLTexture{

public:
    
    void initWithImage(const std::string& path);
    
public:

	static void activeTexture(GLenum texture);

	void generateMipmap(GLenum target);

	void genTextures();

	void bindTexture(GLenum target);

	void texParameteri(GLenum target, GLenum pname, GLint param);

	void texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

    GLuint getTexture();
    
protected:

	GLuint m_textures;
};

#endif
