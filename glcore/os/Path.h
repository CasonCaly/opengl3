//
//  Path.hpp
//  TouchCone
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp
#include "GLCore.h"
#include <stdio.h>
#include <string>
using namespace std;

class GLCORE Path{

public:
    
    static string runDir();
    
    static string resouceDir();
    
    static string joinResource(const string& subPath);
    
protected:
    
    static string s_runDir;
    static string s_resourceDir;
};

#endif /* Path_hpp */
