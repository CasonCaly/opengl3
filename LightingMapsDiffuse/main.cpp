//
//  main.cpp
//  LightingMapsDiffuse
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "LightingMapsDiffuse.h"

int main(void)
{
	LightingMapsDiffuse app;
	app.initGLApp("Lighting Maps Diffuse");
	app.init();
	app.run();
	return 0;
}
