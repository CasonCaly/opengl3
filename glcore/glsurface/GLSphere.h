//
//  GLSphere.hpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/17.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLSphere_hpp
#define GLSphere_hpp

#include "glsurface/GLSurface.h"

class GLCORE GLSphere : public GLSurface
{
public:
    
    GLSphere(float radius, ivec2 division);
    
    vec3 evaluate(const vec2& domain);
    
private:
    
    float m_radius;
};

#endif /* GLCone_hpp */
