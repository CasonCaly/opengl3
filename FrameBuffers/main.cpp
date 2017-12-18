//
//  main.cpp
//  FrameBuffers
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "FrameBuffers.h"

int main(void)
{
	FrameBuffers app;
	app.initGLApp("Frame Buffers", 1280, 720);
	app.init();
	app.run();
	return 0;
}
