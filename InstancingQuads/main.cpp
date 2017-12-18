//
//  main.cpp
//  InstancingQuads
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "InstancingQuads.h"

int main(void)
{
	InstancingQuads app;
	app.initGLApp("Instancing Quads", 1280, 720);
	app.init();
	app.run();
	return 0;
}
