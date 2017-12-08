//
//  main.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "Textures.h"

int main(void)
{
	Textures app;
	app.initGLApp("Textures");
	app.init();
	app.run();
	return 0;
}
