#include "GLCube.h"

GLCube::GLCube(float height){
	m_height = height;
}

int GLCube::getVertexCount(){
	return 4 * 6;//每个面4个顶点，总共6个面
}

int GLCube::getLineIndexCount(){
	return 8;
}

int GLCube::getTriangleIndexCount(){
    return 6 * 6;

}

void GLCube::generateVertices(){
    float halfHeight = m_height/2;
    GLfloat vertex[] = {
        //前
		 halfHeight,  halfHeight,  halfHeight, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,//0
         halfHeight, -halfHeight,  halfHeight, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,//1
        -halfHeight, -halfHeight,  halfHeight, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,//2
        -halfHeight,  halfHeight,  halfHeight, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,//3
        //左
        -halfHeight,  halfHeight,  halfHeight, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//4
        -halfHeight, -halfHeight,  halfHeight, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,//5
        -halfHeight, -halfHeight, -halfHeight, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//6
        -halfHeight,  halfHeight, -halfHeight, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//7
        //后
        -halfHeight,  halfHeight, -halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,//8
        -halfHeight, -halfHeight, -halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,//9
         halfHeight, -halfHeight, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, //10
         halfHeight,  halfHeight, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,//11
        //右
        halfHeight,  halfHeight, -halfHeight, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//12
        halfHeight, -halfHeight, -halfHeight, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,//13
        halfHeight, -halfHeight,  halfHeight, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,//14
        halfHeight,  halfHeight,  halfHeight, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//15
        //上
        halfHeight,  halfHeight, -halfHeight, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,//16
        halfHeight,  halfHeight,  halfHeight, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,//17
       -halfHeight,  halfHeight,  halfHeight, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,//18
       -halfHeight,  halfHeight, -halfHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//19
        //下
       -halfHeight, -halfHeight, -halfHeight, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,//20
       -halfHeight, -halfHeight,  halfHeight, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,//21
        halfHeight, -halfHeight,  halfHeight, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,//22
        halfHeight, -halfHeight, -halfHeight, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,//23

	};


	m_vertexBuffer.gen();
	m_vertexBuffer.bind(GL_ARRAY_BUFFER);
    m_vertexBuffer.setData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
}

void GLCube::generateLineIndices()
{
    GLushort indices[] =
    {
        0, 1, 3,
        1, 2, 3,
        
        4, 5, 7,
        5, 6, 7,
        
        8, 9, 11,
        9, 10, 11,
        
        12, 13, 15,
        13, 14, 15,
        
        16, 17, 19,
        17, 18, 19,
        
        20, 21, 23,
        21, 22, 23
    };
    
    m_indexBuffer.gen();
    m_indexBuffer.bind(GL_ARRAY_BUFFER);
    m_indexBuffer.setData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void GLCube::generateTriangleIndices(){
    GLushort indices[] =
    {
        0, 1, 3,
        1, 2, 3,
        
        4, 5, 7,
        5, 6, 7,
        
        8, 9, 11,
        9, 10, 11,
        
        12, 13, 15,
        13, 14, 15,
        
        16, 17, 19,
        17, 18, 19,
        
        20, 21, 23,
        21, 22, 23
    };
    
    m_triangleIndexBuffer.gen();
    m_triangleIndexBuffer.bind(GL_ARRAY_BUFFER);
    m_triangleIndexBuffer.setData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
