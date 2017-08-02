#ifndef GL_Image_h
#define GL_Image_h
#include <string>
#include "GLCore.h"
//#include "GLGL.h"

class GLCORE GLImage{

	enum class Format
	{
		//! JPEG
		JPG,
		//! PNG
		PNG,
		//! TIFF
		TIFF,
		//! WebP
		WEBP,
		//! PVR
		PVR,
		//! ETC
		ETC,
		//! S3TC
		S3TC,
		//! ATITC
		ATITC,
		//! TGA
		TGA,
		//! Raw Data
		RAW_DATA,
		//! Unknown format
		UNKNOWN
	};

public:

	GLImage();

	~GLImage();

	bool initWithImage(const std::string& path);

    unsigned char* getData();
    
    size_t getWidth();
    
    size_t getHeight();
    
    int getInternalFormat();
    
protected:

	bool initWithPngData(const unsigned char * data, size_t dataLen);

	bool initWithJpgData(const unsigned char * data, size_t dataLen);

	GLImage::Format detectFormat(const unsigned char * data, size_t dataLen);

	bool isPng(const unsigned char * data, size_t dataLen);

	bool isJpg(const unsigned char * data, size_t dataLen);

protected:
    int m_internalFormat;
	Format m_fileType;
	size_t m_width;
	size_t m_height;
	size_t m_dataLen;
	unsigned char* m_data;
};
#endif
