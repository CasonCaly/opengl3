#pragma once

#include "glsurface/GLSurface.h"

class GLCORE GLCube : public GLSurface{

public:

	GLCube(float height);

public:

	virtual int getVertexCount();

	virtual int getLineIndexCount();

	virtual int getTriangleIndexCount();

	virtual void generateVertices();

	virtual void generateLineIndices();

	virtual void generateTriangleIndices();

protected:

	float m_height;
};