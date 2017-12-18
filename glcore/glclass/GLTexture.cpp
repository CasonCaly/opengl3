#include "GLTexture.h"
#include "image/GLImage.h"

void GLTexture::initWithImage(const std::string& path)
{
    GLImage image;
    image.initWithImage(path);
    GLint param = 4;
    size_t bytePerPix = 4;
    if(image.getInternalFormat() == GL_RGB){
        bytePerPix = 3;
    }
    
    size_t width = image.getWidth();
    size_t bytesPerRow = width * bytePerPix / 8;
    if(bytesPerRow % 8 == 0)
    {
        param = 8;
    }
    else if(bytesPerRow % 4 == 0)
    {
        param = 4;
    }
    else if(bytesPerRow % 2 == 0)
    {
        param = 2;
    }
    else
    {
        param = 1;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, param);
    this->genTextures();
    this->bindTexture(GL_TEXTURE_2D);
    this->texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    this->texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    this->texImage2D(GL_TEXTURE_2D,
                          0,
                          image.getInternalFormat(),
                          (GLsizei)image.getWidth(),
                          (GLsizei)image.getHeight(),
                          0,
                          image.getInternalFormat(),
                          GL_UNSIGNED_BYTE,
                          image.getData());
}

void GLTexture::initWithCubemap(std::vector< std::string >& cubemap)
{
    this->genTextures();
    this->bindTexture(GL_TEXTURE_CUBE_MAP);
    for(int i = 0; i < cubemap.size(); i++)
    {
        GLImage image;
        image.initWithImage(cubemap[i]);
        GLint param = 4;
        size_t bytePerPix = 4;
        if(image.getInternalFormat() == GL_RGB){
            bytePerPix = 3;
        }
        
        size_t width = image.getWidth();
        size_t bytesPerRow = width * bytePerPix / 8;
        if(bytesPerRow % 8 == 0)
        {
            param = 8;
        }
        else if(bytesPerRow % 4 == 0)
        {
            param = 4;
        }
        else if(bytesPerRow % 2 == 0)
        {
            param = 2;
        }
        else
        {
            param = 1;
        }
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, param);
        this->texImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0,
                         image.getInternalFormat(),
                         (GLsizei)image.getWidth(),
                         (GLsizei)image.getHeight(),
                         0,
                         image.getInternalFormat(),
                         GL_UNSIGNED_BYTE,
                         image.getData());
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void GLTexture::activeTexture(GLenum texture)
{
	glActiveTexture(texture);
}

void GLTexture::generateMipmap(GLenum target)
{
    m_target = target;
	glGenerateMipmap(target);
}

void GLTexture::genTextures()
{
	glGenTextures(1, &m_textures);
}

void GLTexture::genTextures(GLenum target)
{
    m_target = target;
    glGenTextures(1, &m_textures);
}

void GLTexture::bindTexture(GLenum target)
{
    m_target = target;
	glBindTexture(target, m_textures);
}

void GLTexture::texParameteri(GLenum target, GLenum pname, GLint param)
{
    m_target = target;
	glTexParameteri(target, pname, param);
}

void GLTexture::texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    m_target = target;
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void GLTexture::texImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    m_target = target;
    glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void GLTexture::bindTexture()
{
    glBindTexture(m_target, m_textures);
}

void GLTexture::generateMipmap()
{
    glGenerateMipmap(m_target);
}

void GLTexture::texParameteri(GLenum pname, GLint param)
{
    glTexParameteri(m_target, pname, param);
}

void GLTexture::texImage2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    glTexImage2D(m_target, level, internalformat, width, height, border, format, type, pixels);
}

void GLTexture::texImage2DMultisample(GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    glTexImage2DMultisample(m_target, samples, internalformat, width, height, fixedsamplelocations);
}

GLuint GLTexture::getTexture()
{
    return m_textures;
}

GLenum GLTexture::getTarget()
{
    return m_target;
}

void GLTexture::unbind()
{
    glBindTexture(m_target, 0);
}
