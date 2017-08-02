//
//  GLSurface.hpp
//  glsurface
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLSurface.h"

GLSurface::GLSurface()
{
	m_scale = 1.0f;
	m_enableVertexNormal = false;
    m_enableTexture = false;
}

GLSurface::~GLSurface()
{
}

int GLSurface::getVertexCount()
{
	return m_divisions.x * m_divisions.y; 
}

int GLSurface::getLineIndexCount() 
{
	return 4 * m_slices.x * m_slices.y;
}

int GLSurface::getTriangleIndexCount() 
{
	return 6 * (m_slices.x * m_slices.y);
}

void GLSurface::generateVertices() 
{
	vector<float> vertices;
	int floatsPerVertex = 3;
	
    if (m_enableVertexNormal)
		floatsPerVertex += 3;
    
    if(m_enableTexture)
        floatsPerVertex += 2;
    
	vertices.resize(this->getVertexCount() * floatsPerVertex);
	float* attribute = &vertices[0];

	for (int j = 0; j < m_divisions.y; j++)
	{
		for (int i = 0; i < m_divisions.x; i++)
		{
			vec2 domain = this->computeDomain((float)i, (float)j);
			vec3 range = this->evaluate(domain);
			attribute = range.Write(attribute);

			if (m_enableVertexNormal){
				float s = (float)i, t = (float)j;

				// Nudge the point if the normal is indeterminate.
				if (i == 0) s += 0.01f;
				if (i == m_divisions.x - 1) s -= 0.01f;
				if (j == 0) t += 0.01f;
				if (j == m_divisions.y - 1) t -= 0.01f;

				// Compute the tangents and their cross product.
				vec3 p = this->evaluate(this->computeDomain(s, t));
				vec3 u = this->evaluate(this->computeDomain(s + 0.01f, t)) - p;
				vec3 v = this->evaluate(this->computeDomain(s, t + 0.01f)) - p;
				vec3 normal = u.Cross(v).Normalized();
				if (this->invertNormal(domain))
					normal = -normal;
				attribute = normal.Write(attribute);
			}
            
            if (m_enableTexture) {
                float s = (i%2) == 0 ? 0.0f : 1.0f;
                float t = (j%2) == 0 ? 1.0f : 0.0f;
                //float s = m_textureCount.x * (i*1.0 / m_slices.x);
                //float t = m_textureCount.y * (j*1.0 / m_slices.y);
                attribute = vec2(s, t).Write(attribute);
            }
		}
	}

	m_vertexBuffer.gen();
	m_vertexBuffer.bind(GL_ARRAY_BUFFER);
	m_vertexBuffer.setData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(vertices[0]),
		&vertices[0],
		GL_STATIC_DRAW);
}

void GLSurface::generateLineIndices() 
{
	int indexCount = this->getLineIndexCount();
	vector<GLushort> indices;
	indices.resize(indexCount);
	vector<unsigned short>::iterator index = indices.begin();
	for (int j = 0, vertex = 0; j < m_slices.y; j++) {
		for (int i = 0; i < m_slices.x; i++) {
			int next = (i + 1) % m_divisions.x;
			*index++ = vertex + i;
			*index++ = vertex + next;
			*index++ = vertex + i;
			*index++ = vertex + i + m_divisions.x;
		}
		vertex += m_divisions.x;
	}

	m_indexBuffer.gen();
	m_indexBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuffer.setData(
		GL_ELEMENT_ARRAY_BUFFER, 
		indexCount * sizeof(GLushort),
		&indices[0],
		GL_STATIC_DRAW);
}

void GLSurface::generateTriangleIndices() 
{
	int indexCount = this->getTriangleIndexCount();
	vector<GLushort> indices;
	indices.resize(indexCount);
	vector<GLushort>::iterator index = indices.begin();
	
	for (int j = 0, vertex = 0; j < m_slices.y; j++){
		for (int i = 0; i < m_slices.x; i++){
			int next = (i + 1) % m_divisions.x;
			*index++ = vertex + i;
			*index++ = vertex + next;
			*index++ = vertex + i + m_divisions.x;

			*index++ = vertex + next;
			*index++ = vertex + next + m_divisions.x;
			*index++ = vertex + i + m_divisions.x;
		}
		vertex += m_divisions.x;
	}
	m_triangleIndexBuffer.gen();
	m_triangleIndexBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
	m_triangleIndexBuffer.setData(
		GL_ELEMENT_ARRAY_BUFFER, 
		indexCount * sizeof(GLushort),
		&indices[0],
		GL_STATIC_DRAW);
}

vec2 GLSurface::computeDomain(float x, float y)
{
	return vec2(x * m_upperBound.x / m_slices.x, y * m_upperBound.y / m_slices.y);
}

void GLSurface::setInterval(const GLInterval& interval)
{
    m_divisions = interval.divisions;
    m_upperBound = interval.upperBound;
    m_textureCount = interval.textureCount;
    m_slices = m_divisions - ivec2(1, 1);
}

vec3 GLSurface::evaluate(const vec2& domain)
{
	return vec3();
}

bool GLSurface::invertNormal(const vec2& domain)
{
	return false; 
}

GLBuffer& GLSurface::getVertexBuffer()
{
	return m_vertexBuffer;
}

GLBuffer& GLSurface::getIndexBuffer()
{
	return m_indexBuffer;
}

GLBuffer& GLSurface::getTriangleIndexBuffer()
{
	return m_triangleIndexBuffer;
}

vec2 GLSurface::getLowerLeft()
{
	return m_lowerLeft;
}

vec2 GLSurface::getViewportSize()
{
	return m_viewportSize;
}

void GLSurface::setLowerLeft(const vec2& lowerLeft)
{
	m_lowerLeft = lowerLeft;
}

void GLSurface::setViewportSize(const vec2& viewportSize)
{
	m_viewportSize = viewportSize;
}

void GLSurface::setColor(const vec3& color)
{
	m_color = color;
}

vec3 GLSurface::getColor()
{
	return m_color;
}

Quaternion& GLSurface::getOrientation(){
	return m_orientation;
}

void GLSurface::setOrientation(const Quaternion& orientation)
{
	m_orientation = orientation;
}

void GLSurface::setEnableVertexNormal(bool enableVertexNormal)
{
	m_enableVertexNormal = enableVertexNormal;
}

void GLSurface::setEnableTexture(bool enableTexture)
{
    m_enableTexture = enableTexture;
}

bool GLSurface::isEnableTexture()
{
    return m_enableTexture;
}


void GLSurface::setName(const std::string& name)
{
	m_name = name;
}

std::string& GLSurface::getName()
{
	return m_name;
}

void GLSurface::setTextureCount(vec2 v)
{
    m_textureCount = v;
}

void GLSurface::setScale(float scale){
	m_scale = scale;
}

float GLSurface::getScale()
{
	return m_scale;
}
