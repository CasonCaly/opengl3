//
//  main.cpp
//  MultipleLights
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "MultipleLights.h"

int main(void)
{
	MultipleLights app;
	app.initGLApp("Multiple Lights");
	app.init();
	app.run();
	return 0;
}
