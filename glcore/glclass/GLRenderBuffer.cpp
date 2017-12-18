#include "GLRenderBuffer.h"

GLRenderBuffer::GLRenderBuffer()
{
	m_renderBuffer = 0;
}

void GLRenderBuffer::gen()
{
    glGenRenderbuffers(1, &m_renderBuffer);
}

void GLRenderBuffer::bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
}

void GLRenderBuffer::renderbufferStorage(GLenum internalformat, int width, int height)
{
    glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
}

void GLRenderBuffer::storageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
}

GLuint GLRenderBuffer::renderBuffer()
{
    return m_renderBuffer;
}

void GLRenderBuffer::unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
