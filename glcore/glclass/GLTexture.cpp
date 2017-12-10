#include "GLTexture.h"
#include "image/GLImage.h"

//typedef Texture2D::PixelFormatInfoMap::value_type PixelFormatInfoMapValue;
//static const PixelFormatInfoMapValue TexturePixelFormatInfoTablesValue[] =
//{
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::BGRA8888, Texture2D::PixelFormatInfo(GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::RGBA8888, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::RGBA4444, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB5A1, Texture2D::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB565, Texture2D::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::RGB888, Texture2D::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::A8, Texture2D::PixelFormatInfo(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::I8, Texture2D::PixelFormatInfo(GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false)),
//    PixelFormatInfoMapValue(Texture2D::PixelFormat::AI88, Texture2D::PixelFormatInfo(GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true)),
//    
//
//};
//}

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

    //glPixelStorei(GL_UNPACK_ALIGNMENT, param);
    this->genTextures();
    this->bindTexture(GL_TEXTURE_2D);
//    this->texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    this->texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
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

void GLTexture::activeTexture(GLenum texture)
{
	glActiveTexture(texture);
}

void GLTexture::generateMipmap(GLenum target)
{
	glGenerateMipmap(target);
}

void GLTexture::genTextures(){
	glGenTextures(1, &m_textures);
}

void GLTexture::bindTexture(GLenum target){
	glBindTexture(target, m_textures);
}

void GLTexture::texParameteri(GLenum target, GLenum pname, GLint param)
{
	glTexParameteri(target, pname, param);
}

void GLTexture::texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

GLuint GLTexture::getTexture()
{
    return m_textures;
}
