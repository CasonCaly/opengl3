//
//  main.cpp
//  LightingMapsSpecular
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "LightingMapsSpecular.h"

int main(void)
{
	LightingMapsSpecular app;
	app.initGLApp("Lighting Maps Specular");
	app.init();
	app.run();
	return 0;
}
