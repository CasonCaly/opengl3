//
//  main.cpp
//  TexturesCombined
//
//  Created by zhuang yusong on 2017/3/4.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include <iostream>
#include "TexturesCombined.h"

int main(void)
{
	TexturesCombined app;
	app.initGLApp("Textures Combined");
	app.init();
	app.run();
	return 0;
}
