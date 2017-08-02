#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "glclass/GLGL.h"
#include "GLImage.h"
#include "os/Path.h"
#include "png.h"
#include "jpeglib.h"

#define CC_BREAK_IF(cond)           if(cond) break

typedef struct
{
	const unsigned char * data;
	size_t size;
	int offset;
}tImageSource;

static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);

	if ((int)(isource->offset + length) <= isource->size)
	{
		memcpy(data, isource->data + isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

struct MyErrorMgr
{
	struct jpeg_error_mgr pub;  /* "public" fields */
	jmp_buf setjmp_buffer;  /* for return to caller */
};

typedef struct MyErrorMgr * MyErrorPtr;

/*
* Here's the routine that will replace the standard error_exit method:
*/

METHODDEF(void)
myErrorExit(j_common_ptr cinfo)
{
	/* cinfo->err really points to a MyErrorMgr struct, so coerce pointer */
	MyErrorPtr myerr = (MyErrorPtr)cinfo->err;

	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	/* internal message function can't show error message in some platforms, so we rewrite it here.
	* edit it if has version conflict.
	*/
	//(*cinfo->err->output_message) (cinfo);
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message) (cinfo, buffer);
	printf("jpeg error: %s", buffer);

	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}

GLImage::GLImage()
{
	m_fileType = Format::UNKNOWN;
    m_internalFormat = GL_RGBA;
	m_width = 0;
	m_height = 0;
	m_dataLen = 0;
	m_data = nullptr;
}

GLImage::~GLImage()
{
	if (m_data)
		free(m_data);
}

unsigned char* GLImage::getData()
{
    return m_data;
}

size_t GLImage::getWidth()
{
    return m_width;
}

size_t GLImage::getHeight()
{
    return m_height;
}

GLint GLImage::getInternalFormat()
{
    return m_internalFormat;
}

bool GLImage::initWithImage(const std::string& path)
{
	std::string fullPath = Path::joinResource(path);
	FILE* file = fopen(fullPath.c_str(), "rb");
	if (!file){
		printf("file not exist %s", path.c_str());
		return false;
	}
	fseek(file, 0, SEEK_END);
	long unpackedLen = ftell(file);
	unsigned char* unpackedData = (unsigned char*)malloc(unpackedLen* sizeof(char));
	fseek(file, -unpackedLen, SEEK_CUR);
	fread(unpackedData, 1, unpackedLen, file);
	fclose(file);

	m_fileType = detectFormat(unpackedData, unpackedLen);
	bool ret = false;
	switch (m_fileType)
	{
	case Format::PNG:
		ret = this->initWithPngData(unpackedData, unpackedLen);
		break;
	case Format::JPG:
		ret = initWithJpgData(unpackedData, unpackedLen);
		break;
    default:
        break;
	}
	if (unpackedData)
		free(unpackedData);
	return ret;
}

bool GLImage::initWithPngData(const unsigned char * data, size_t dataLen)
{
	// length of bytes to check if it is a valid png file
	#define PNGSIGSIZE  8
	bool ret = false;
	png_byte        header[PNGSIGSIZE] = { 0 };
	png_structp     png_ptr = 0;
	png_infop       info_ptr = 0;

	do
	{
		// png header len is 8 bytes
		CC_BREAK_IF(dataLen < PNGSIGSIZE);

		// check the data is png or not
		memcpy(header, data, PNGSIGSIZE);
		CC_BREAK_IF(png_sig_cmp(header, 0, PNGSIGSIZE));

		// init png_struct
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		CC_BREAK_IF(!png_ptr);

		// init png_info
		info_ptr = png_create_info_struct(png_ptr);
		CC_BREAK_IF(!info_ptr);

		// set the read call back function
		tImageSource imageSource;
		imageSource.data = (unsigned char*)data;
		imageSource.size = dataLen;
		imageSource.offset = 0;
		png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

		// read png header info

		// read png file info
		png_read_info(png_ptr, info_ptr);

		m_width = png_get_image_width(png_ptr, info_ptr);
		m_height = png_get_image_height(png_ptr, info_ptr);
		png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

		//CCLOG("color type %u", color_type);

		// force palette images to be expanded to 24-bit RGB
		// it may include alpha channel
		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			png_set_palette_to_rgb(png_ptr);
		}
		// low-bit-depth grayscale images are to be expanded to 8 bits
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		{
			bit_depth = 8;
			png_set_expand_gray_1_2_4_to_8(png_ptr);
		}
		// expand any tRNS chunk data into a full alpha channel
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(png_ptr);
		}
		// reduce images with 16-bit samples to 8 bits
		if (bit_depth == 16)
		{
			png_set_strip_16(png_ptr);
		}

		// Expanded earlier for grayscale, now take care of palette and rgb
		if (bit_depth < 8)
		{
			png_set_packing(png_ptr);
		}
		// update info
		png_read_update_info(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);

		switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
			//_renderFormat = Texture2D::PixelFormat::I8;
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			//_renderFormat = Texture2D::PixelFormat::AI88;
			break;
		case PNG_COLOR_TYPE_RGB:
            m_internalFormat = GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
            m_internalFormat = GL_RGBA;
			break;
		default:
			break;
		}

		// read png data
		png_size_t rowbytes;
		png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep)* m_height);

		rowbytes = png_get_rowbytes(png_ptr, info_ptr);

		m_dataLen = rowbytes * m_height;
		m_data = static_cast<unsigned char*>(malloc(m_dataLen * sizeof(unsigned char)));
		if (!m_data)
		{
			if (row_pointers != nullptr)
			{
				free(row_pointers);
			}
			break;
		}

		for (unsigned short i = 0; i < m_height; ++i)
		{
			row_pointers[i] = m_data + i*rowbytes;
		}
		png_read_image(png_ptr, row_pointers);

		png_read_end(png_ptr, nullptr);

		// premultiplied alpha for RGBA8888
		//if (PNG_PREMULTIPLIED_ALPHA_ENABLED && color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		//{
		//	premultipliedAlpha();
		//}

		if (row_pointers != nullptr)
		{
			free(row_pointers);
		}

		ret = true;
	} while (0);

	if (png_ptr)
	{
		png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
	}
	return ret;
}

bool GLImage::initWithJpgData(const unsigned char * data, size_t dataLen)
{
	/* these are standard libjpeg structures for reading(decompression) */
	struct jpeg_decompress_struct cinfo;
	/* We use our private extension JPEG error handler.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/
	struct MyErrorMgr jerr;
	/* libjpeg data structure for storing one row, that is, scanline of an image */
	JSAMPROW row_pointer[1] = { 0 };
	unsigned long location = 0;

	bool ret = false;
	do
	{
		/* We set up the normal JPEG error routines, then override error_exit. */
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = myErrorExit;
		/* Establish the setjmp return context for MyErrorExit to use. */
		if (setjmp(jerr.setjmp_buffer))
		{
			/* If we get here, the JPEG code has signaled an error.
			* We need to clean up the JPEG object, close the input file, and return.
			*/
			jpeg_destroy_decompress(&cinfo);
			break;
		}

		/* setup decompression process and source, then read JPEG header */
		jpeg_create_decompress(&cinfo);

#ifndef CC_TARGET_QT5
		jpeg_mem_src(&cinfo, const_cast<unsigned char*>(data), dataLen);
#endif /* CC_TARGET_QT5 */

		/* reading the image header which contains image information */
#if (JPEG_LIB_VERSION >= 90)
		// libjpeg 0.9 adds stricter types.
		jpeg_read_header(&cinfo, TRUE);
#else
		jpeg_read_header(&cinfo, TRUE);
#endif

		// we only support RGB or grayscale
		if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
		{
			//_renderFormat = Texture2D::PixelFormat::I8;
		}
		else
		{
			cinfo.out_color_space = JCS_RGB;
            m_internalFormat = GL_RGB;
			//_renderFormat = Texture2D::PixelFormat::RGB888;
		}

		/* Start decompression jpeg here */
		jpeg_start_decompress(&cinfo);

		/* init image info */
		m_width = cinfo.output_width;
		m_height = cinfo.output_height;

		m_dataLen = cinfo.output_width*cinfo.output_height*cinfo.output_components;
		m_data = static_cast<unsigned char*>(malloc(m_dataLen * sizeof(unsigned char)));
		CC_BREAK_IF(!m_data);

		/* now actually read the jpeg into the raw buffer */
		/* read one scan line at a time */
		while (cinfo.output_scanline < cinfo.output_height)
		{
			row_pointer[0] = m_data + location;
			location += cinfo.output_width*cinfo.output_components;
			jpeg_read_scanlines(&cinfo, row_pointer, 1);
		}

		/* When read image file with broken data, jpeg_finish_decompress() may cause error.
		* Besides, jpeg_destroy_decompress() shall deallocate and release all memory associated
		* with the decompression object.
		* So it doesn't need to call jpeg_finish_decompress().
		*/
		//jpeg_finish_decompress( &cinfo );
		jpeg_destroy_decompress(&cinfo);
		/* wrap up decompression, destroy objects, free pointers and close open files */
		ret = true;
	} while (0);

	return ret;
}

GLImage::Format GLImage::detectFormat(const unsigned char * data, size_t dataLen)
{
	if (isPng(data, dataLen))
	{
		return Format::PNG;
	}
	else if (isJpg(data, dataLen))
	{
		return Format::JPG;
	}
	else
	{
		return Format::UNKNOWN;
	}
}

bool GLImage::isPng(const unsigned char * data, size_t dataLen)
{
	if (dataLen <= 8)
	{
		return false;
	}

	static const unsigned char PNG_SIGNATURE[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

	return memcmp(PNG_SIGNATURE, data, sizeof(PNG_SIGNATURE)) == 0;
}

bool GLImage::isJpg(const unsigned char * data, size_t dataLen)
{
	if (dataLen <= 4)
	{
		return false;
	}

	static const unsigned char JPG_SOI[] = { 0xFF, 0xD8 };

	return memcmp(data, JPG_SOI, 2) == 0;
}
