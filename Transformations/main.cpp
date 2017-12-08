//
//  main.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "Transformations.h"

int main(void)
{
	Transformations app;
	app.initGLApp("Transformations");
	app.init();
	app.run();
	return 0;
}
