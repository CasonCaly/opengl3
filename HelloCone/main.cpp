//
//  main.cpp
//  HelloArrow
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "HelloCone.h"

int main(void)
{
	HelloCone app;
	app.initGLApp("Hello Cone");
	app.init();
	app.run();
	return 0;
}
