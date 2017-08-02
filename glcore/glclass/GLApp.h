//
//  GLApp.hpp
//  TouchCone
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLApp_hpp
#define GLApp_hpp
#include "GLCore.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "GLProgram.h"
#include "math/Quaternion.hpp"
#include "math/Vector.hpp"

class GLCORE GLApp{
  
public:

	GLApp();

    void initGLApp(const std::string& appName, int width, int height);
    
	void initGLApp(const std::string& appName);

	void run();

public:

	virtual void render();

public:
    
    virtual void onTouchBegan(float x, float y);
    
    virtual void onTouchMove(float x, float y);
    
    virtual void onTouchEnd(float x, float y);
    
	virtual void onMouseScroll(double x, double y);

    virtual void initProgram();
    
protected:
    
    char* readShader(const string& path);
    
	void createPrograme(const string& frag, const string& vert, GLProgram& program);

protected:
    int m_width;
    int m_height;
    GLProgram m_glProgram;
};


#endif /* GLApp_hpp */
