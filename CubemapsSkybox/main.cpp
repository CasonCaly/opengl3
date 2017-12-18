//
//  main.cpp
//  CubemapsSkybox
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "CubemapsSkybox.h"

int main(void)
{
	CubemapsSkybox app;
	app.initGLApp("Cubemaps Skybox", 1280, 720);
	app.init();
	app.run();
	return 0;
}
