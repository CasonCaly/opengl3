//
//  main.cpp
//  AntiAliasingPostProcessing
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "AntiAliasingPostProcessing.h"

int main(void)
{
	AntiAliasingPostProcessing app;
	app.initGLApp("Anti Aliasing Post Processing", 1280, 720);
	app.init();
	app.run();
	return 0;
}
