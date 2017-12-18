//
//  main.cpp
//  DepthTesing
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "DepthTesing.h"

int main(void)
{
	DepthTesing app;
	app.initGLApp("Depth Tesing", 1280, 720);
	app.init();
	app.run();
	return 0;
}
