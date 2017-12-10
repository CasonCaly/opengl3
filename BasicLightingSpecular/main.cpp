//
//  main.cpp
//  BasicLightingSpecular
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "BasicLightingSpecular.h"

int main(void)
{
	BasicLightingSpecular app;
	app.initGLApp("Basic Lighting Specular");
	app.init();
	app.run();
	return 0;
}
