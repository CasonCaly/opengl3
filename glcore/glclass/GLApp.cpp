//
//  GLApp.cpp
//  TouchCone
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//
#include <stdlib.h>
#if defined(WIN32)
#include <glew.h>
#include <wglew.h>
#endif
#include <glfw3.h>
#include "GLApp.h"
#include "os/Path.h"

#if defined(WIN32)
static bool glew_dynamic_binding()
{
	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

	// If the current opengl driver doesn't have framebuffers methods, check if an extension exists
	if (glGenFramebuffers == nullptr)
	{

		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{

			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
		}
		else
		if (strstr(gl_extensions, "EXT_framebuffer_object"))
		{
			cout << "OpenGL: EXT_framebuffer_object is supported" << endl;
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbufferEXT");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbufferEXT");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffersEXT");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorageEXT");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameterivEXT");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebufferEXT");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebufferEXT");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffersEXT");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffersEXT");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatusEXT");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1DEXT");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2DEXT");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3DEXT");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbufferEXT");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmapEXT");
		}
		else
		{
			cout << "OpenGL: No framebuffers extension is supported" << endl;
			cout << "OpenGL: Any call to Fbo will crash!" << endl;
			return false;
		}
	}
	return true;
}

// helper
bool initGlew()
{
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		return false;
	}

	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		cout << "Ready for GLSL" << endl;
	}
	else
	{
		cout << "Not totally ready :(" << endl;
	}

	if (glewIsSupported("GL_VERSION_2_0"))
	{
		cout << "Ready for OpenGL 2.0" << endl;
	}
	else
	{
		cout << "OpenGL 2.0 not supported" << endl;
	}


	if (glew_dynamic_binding() == false)
	{
		cout << "No OpenGL framebuffer support. Please upgrade the driver of your video card." << " OpenGL error" << endl;
		return false;
	}

	return true;
}
#endif

GLApp* g_app;
bool g_captured = false;
GLFWwindow* g_window;

static void  GLAppMouseMoveCallBack(GLFWwindow* window, double x, double y){
	if (g_captured)
		g_app->onTouchMove((float)x, (float)y);
}

static void GLAppMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{
	double mouseX;
	double mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if (GLFW_MOUSE_BUTTON_LEFT == button){
		if (GLFW_PRESS == action){
			g_captured = true;
			g_app->onTouchBegan((float)mouseX, (float)mouseY);

		}
		else if (GLFW_RELEASE == action){
			if (g_captured){
				g_captured = false;
				g_app->onTouchEnd((float)mouseX, (float)mouseY);
			}
		}
	}
}

static void GLAppMouseScrollCallBack(GLFWwindow* window, double x, double y)
{
	if (g_app)
		g_app->onMouseScroll(x, y);
}

GLApp::GLApp()
{
	g_app = this;
}

void GLApp::initGLApp(const std::string& appName, int width, int height)
{
    m_width = width;
    m_height = height;
    /* Initialize the library */
    if (!glfwInit())
        return ;
    
    /* Create a windowed mode window and its OpenGL context */
    g_window = glfwCreateWindow(width, height, appName.c_str(), NULL, NULL);
    
    if (!g_window){
        glfwTerminate();
    }
    //8, 8, 8, 8, 24, 8
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    
    glfwSetCursorPosCallback(g_window, GLAppMouseMoveCallBack);
    glfwSetMouseButtonCallback(g_window, GLAppMouseCallBack);
    glfwSetScrollCallback(g_window, GLAppMouseScrollCallBack);
    glfwMakeContextCurrent(g_window);
    
#if defined(WIN32)
    ::initGlew();
#endif
    
    this->initProgram();

}

void GLApp::initGLApp(const std::string& appName)
{
    this->initGLApp(appName, 640, 960);
}

void GLApp::run()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(g_window)){
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		this->render();
		/* Swap front and back buffers */
		glfwSwapBuffers(g_window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

void GLApp::onTouchBegan(float x, float y){
    
}

void GLApp::onTouchMove(float x, float y){

}

void GLApp::onTouchEnd(float x, float y){
}

void GLApp::onMouseScroll(double x, double y)
{

}

void GLApp::render()
{

}

void GLApp::initProgram()
{
	this->createPrograme("Shaders/Simple.vert", "Shaders/Simple.frag", m_glProgram);
	m_glProgram.use();
}


void GLApp::createPrograme(const string& frag, const string& vert, GLProgram& program)
{
	GLShader vertexShader;
	vertexShader.createVertex();
	char* szVertexShader = this->readShader(Path::joinResource(frag.c_str()));
	vertexShader.compile(szVertexShader);
	free(szVertexShader);

	GLShader fragmentShader;
	fragmentShader.createFragment();
	char* szFragmentShader = this->readShader(Path::joinResource(vert.c_str()));
	fragmentShader.compile(szFragmentShader);
	free(szFragmentShader);

	program.create();
	program.attachShader(vertexShader);
	program.attachShader(fragmentShader);
	program.link();
}

char* GLApp::readShader(const string& path){
    FILE* file = fopen(path.c_str(), "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    char* ctn = (char*)malloc((size + 1) *sizeof(char));
    fseek(file, -size, SEEK_CUR);
    fread(ctn, 1, size, file);
    ctn[size] = 0;
    fclose(file);
    return ctn;
}
