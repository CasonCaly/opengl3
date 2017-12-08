//
//  main.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "HelloTriangleIndexed.h"

int main(void)
{
	HelloTriangleIndexed app;
	app.initGLApp("Hello Triangle Indexed");
	app.init();
	app.run();
	return 0;
}
