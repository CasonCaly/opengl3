#include "GLBuffer.h"

GLBuffer::GLBuffer()
{
	m_vertexBuffer = 0;
}

void GLBuffer::gen()
{
	glGenBuffers(1, &m_vertexBuffer);
}

void GLBuffer::bind(GLenum target)
{
    m_target = target;
	glBindBuffer(target, m_vertexBuffer);
}

void GLBuffer::setData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}

void GLBuffer::unbind()
{
    glBindBuffer(m_target, 0);
}
