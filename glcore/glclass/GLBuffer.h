#ifndef GL_BUFFER_H
#define GL_BUFFER_H
#include "GLGL.h"

class GLCORE GLBuffer
{
public:

	GLBuffer();

	void gen();

	void bind(GLenum target);

	void setData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);

    void unbind();
    
private:

    GLenum m_target;
    
	GLuint m_vertexBuffer;
};

#endif
