//
//  main.cpp
//  ShadersUniform
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "ShadersUniform.h"

int main(void)
{
	ShadersUniform app;
	app.initGLApp("Shaders Uniform");
	app.init();
	app.run();
	return 0;
}
