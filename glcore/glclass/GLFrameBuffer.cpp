#include "GLFrameBuffer.h"

void GLFrameBuffer::bindDefault()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLFrameBuffer::GLFrameBuffer()
{
	m_frameBuffer = 0;
}

void GLFrameBuffer::gen()
{
    glGenFramebuffers(1, &m_frameBuffer);
}

void GLFrameBuffer::bindDraw()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBuffer);
}

void GLFrameBuffer::bindRead()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);
}

void GLFrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
}

void GLFrameBuffer::renderbuffer(GLRenderBuffer& renderBuffer)
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.renderBuffer());
}

void GLFrameBuffer::texture2D(GLTexture& texture)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture.getTarget(), texture.getTexture(), 0);
}

bool GLFrameBuffer::checkStatusComplete()
{
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    return status != GL_FRAMEBUFFER_COMPLETE;
}

void GLFrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint GLFrameBuffer::framebuffer()
{
    return m_frameBuffer;
}
