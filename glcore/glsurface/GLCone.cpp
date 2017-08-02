//
//  GLCone.cpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLCone.h"

GLCone::GLCone(float height, float radius, ivec2 division) : m_height(height), m_radius(radius)
{
	GLInterval interval = { division, vec2(TwoPi, 1), vec2(30, 20) };
    this->setInterval(interval);
}

vec3 GLCone::evaluate(const vec2& domain)
{
	float u = domain.x;
	float v = domain.y;
	//根据相似三角形原理，可以得出半径可以进行比例均分
    float x = m_radius * (1 - v) * cos(u);
    float y = m_height * (v - 0.5f);
    float z = m_radius * (1 - v) * -sin(u); //理论上应该是正的
    return vec3(x, y, z);
}
