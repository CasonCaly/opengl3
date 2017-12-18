#ifndef GL_Texture_h
#define GL_Texture_h
#include "GLGL.h"

#include <string>
#include <vector>

class GLCORE GLTexture{

public:
    
    void initWithImage(const std::string& path);
    
    void initWithCubemap(std::vector<std::string>& cubemap);
    
public:

	static void activeTexture(GLenum texture);

    void genTextures();
    
    void genTextures(GLenum target);
    
    void bindTexture(GLenum target);
    
	void generateMipmap(GLenum target);

	void texParameteri(GLenum target, GLenum pname, GLint param);

	void texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

    void texImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
    ////
    void bindTexture();
    
    void generateMipmap();
    
    void texParameteri(GLenum pname, GLint param);
    
    void texImage2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
    
    void texImage2DMultisample(GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
    
    ////
    GLuint getTexture();
    
    GLenum getTarget();
    
    void unbind();
    
protected:
    GLenum m_target;
	GLuint m_textures;
};

#endif
