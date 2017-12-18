#ifndef GLRenderBuffer_H
#define GLRenderBuffer_H
#include "GLGL.h"

class GLCORE GLRenderBuffer
{
public:

	GLRenderBuffer();

	void gen();

    void bind();
    
    void renderbufferStorage(GLenum internalformat, int width, int height);
    
    void storageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
    
    GLuint renderBuffer();
    
    void unbind();
    
private:

	GLuint m_renderBuffer;
};

#endif
