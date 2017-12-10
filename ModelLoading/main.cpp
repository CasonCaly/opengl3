//
//  main.cpp
//  ModelLoading
//
//  Created by zhuang yusong on 2017/12/7.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "ModelLoading.h"

int main(void)
{
	ModelLoading app;
	app.initGLApp("Model Loading");
	app.init();
	app.run();
	return 0;
}
