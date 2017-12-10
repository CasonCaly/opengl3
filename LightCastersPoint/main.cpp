//
//  main.cpp
//  LightCastersPoint
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "LightCastersPoint.h"

int main(void)
{
	LightCastersPoint app;
	app.initGLApp("Light Casters Point");
	app.init();
	app.run();
	return 0;
}
