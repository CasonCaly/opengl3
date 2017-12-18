//
//  main.cpp
//  DepthTesing
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "StencilTesting.h"

int main(void)
{
	StencilTesting app;
	app.initGLApp("Stencil Testing", 1280, 720);
	app.init();
	app.run();
	return 0;
}
