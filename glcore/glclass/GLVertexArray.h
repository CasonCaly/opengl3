#ifndef GL_VERTEX_ARRAY_H
#define GL_VERTEX_ARRAY_H
#include "GLGL.h"

class GLCORE GLVertexArray
{
public:

	GLVertexArray();

	void gen();

    void bind();
    
    void unbind();
    
private:

	GLuint m_vertexArray;
};

#endif
