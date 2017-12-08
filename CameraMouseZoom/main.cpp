//
//  main.cpp
//  CameraMouseZoom
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "CameraMouseZoom.h"

int main(void)
{
	CameraMouseZoom app;
	app.initGLApp("Camera Mouse Zoom");
	app.init();
	app.run();
	return 0;
}
