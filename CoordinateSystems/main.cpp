//
//  main.cpp
//  CoordinateSystems
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "CoordinateSystems.h"

int main(void)
{
	CoordinateSystems app;
	app.initGLApp("Coordinate Systems");
	app.init();
	app.run();
	return 0;
}
