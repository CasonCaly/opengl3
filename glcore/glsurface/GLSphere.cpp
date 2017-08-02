//
//  GLSphere.cpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/17.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLSphere.h"

GLSphere::GLSphere(float radius, ivec2 division) : m_radius(radius)
{
    GLInterval interval = { division, vec2(Pi, TwoPi), vec2(20, 35)};
    this->setInterval(interval);
}

vec3 GLSphere::evaluate(const vec2& domain)
{
    //采用球坐标系的方式来进行参数化表面
    float u = domain.x, v = domain.y;
    float x = m_radius * sin(u) * cos(v);
    float y = m_radius * cos(u);
    float z = m_radius * -sin(u) * sin(v);
    return vec3(x, y, z);
}
