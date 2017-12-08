//
//  main.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "ShadersInterpolation.h"

int main(void)
{
	ShadersInterpolation app;
	app.initGLApp("Shaders Uniform");
	app.init();
	app.run();
	return 0;
}
