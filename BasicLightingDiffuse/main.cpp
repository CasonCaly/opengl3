//
//  main.cpp
//  BasicLightingDiffuse
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "BasicLightingDiffuse.h"

int main(void)
{
	BasicLightingDiffuse app;
	app.initGLApp("Basic Lighting Diffuse");
	app.init();
	app.run();
	return 0;
}
