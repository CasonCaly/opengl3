//
//  Path.cpp
//  TouchCone
//
//  Created by zhuang yusong on 2017/3/5.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//
//#import <Foundation/Foundation.h>
#include <stdlib.h>
#if !defined(WIN32)
#include <mach-o/dyld.h>
#else
#include <windows.h>
#include <psapi.h>   
#pragma comment(lib,"psapi.lib")  
#endif
#include <string.h>
#include "Path.h"

string Path::s_runDir;
string Path::s_resourceDir;

string Path::runDir(){
#if !defined(WIN32)
    if(Path::s_runDir.empty()){
        char buf[0];
        uint32_t size = 0;
        int res = _NSGetExecutablePath(buf,&size);
        
        char* path = (char*)malloc(size+1);
        path[size] = 0;
        res = _NSGetExecutablePath(path,&size);
        
        char* p = strrchr(path, '/');
        *p = 0;
         Path::s_runDir.append(path);
        free(path);  
       
    }
#else
	s_runDir = ".";
#endif        
    return Path::s_runDir;
}

string Path::resouceDir(){
#if !defined(WIN32)
    if(Path::s_resourceDir.empty()){
        string runDir = Path::runDir();
        size_t index = runDir.find_last_of("/");
        Path::s_resourceDir = runDir.substr(0, index);
        Path::s_resourceDir.append("/Resources");
    }
#else
	s_resourceDir = ".";
#endif       
    return Path::s_resourceDir;
}

string Path::joinResource(const string& subPath){
    
    string path = Path::resouceDir();
    if(subPath.find(path) == 0)
    {
        return subPath;
    }
    path.append("/");
    path.append(subPath);
    return path;
}
