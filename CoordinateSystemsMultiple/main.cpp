//
//  main.cpp
//  CoordinateSystemsMultiple
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "CoordinateSystemsMultiple.h"

int main(void)
{
	CoordinateSystemsMultiple app;
	app.initGLApp("Coordinate Systems Multiple");
	app.init();
	app.run();
	return 0;
}
