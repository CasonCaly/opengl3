//
//  main.cpp
//  CameraCircle
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "CameraCircle.h"

int main(void)
{
	CameraCircle app;
	app.initGLApp("Camera Circle");
	app.init();
	app.run();
	return 0;
}
