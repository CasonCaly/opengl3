//
//  main.cpp
//  Materials
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "Materials.h"

int main(void)
{
	Materials app;
	app.initGLApp("Materials");
	app.init();
	app.run();
	return 0;
}
