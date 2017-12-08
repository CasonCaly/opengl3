//
//  main.cpp
//  CameraKeyboardDt
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "CameraKeyboardDt.h"

int main(void)
{
	CameraKeyboardDt app;
	app.initGLApp("Camera Keyboard Dt");
	app.init();
	app.run();
	return 0;
}
