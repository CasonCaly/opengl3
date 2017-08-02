#ifndef GL_GL_H
#define GL_GL_H
#include "GLCore.h"
#if defined(WIN32)
#include <glew.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#endif

#endif