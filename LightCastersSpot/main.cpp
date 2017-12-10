//
//  main.cpp
//  LightCastersSpot
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "LightCastersSpot.h"

int main(void)
{
	LightCastersSpot app;
	app.initGLApp("Light Casters Spot");
	app.init();
	app.run();
	return 0;
}
