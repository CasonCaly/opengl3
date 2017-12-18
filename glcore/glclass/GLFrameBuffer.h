#ifndef GLFrameBuffer_H
#define GLFrameBuffer_H
#include "GLGL.h"
#include "GLRenderBuffer.h"
#include "GLTexture.h"

class GLCORE GLFrameBuffer
{
public:

    static void bindDefault();
    
	GLFrameBuffer();

	void gen();

    void bindDraw();
    
    void bindRead();
    
    void bind();
    
    void renderbuffer(GLRenderBuffer& renderBuffer);
    
    void texture2D(GLTexture& texture);
    
    bool checkStatusComplete();
    
    void unbind();
    
    GLuint framebuffer();
    
private:

	GLuint m_frameBuffer;
};

#endif
