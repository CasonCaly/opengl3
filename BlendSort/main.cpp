//
//  main.cpp
//  BlendSort
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "BlendSort.h"

int main(void)
{
	BlendSort app;
	app.initGLApp("Blend Sort", 1280, 720);
	app.init();
	app.run();
	return 0;
}
