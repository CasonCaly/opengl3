//
//  GLCone.cpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLTorus.h"

GLTorus::GLTorus(float majorRadius, float minorRadius, ivec2 division) : m_majorRadius(majorRadius),
m_minorRadius(minorRadius)
{
	GLInterval interval = { division, vec2(TwoPi, TwoPi), vec2(30, 20) };
    this->setInterval(interval);
}

vec3 GLTorus::evaluate(const vec2& domain)
{
	const float major = m_majorRadius;
	const float minor = m_minorRadius;
	float u = domain.x, v = domain.y;
	float x = (major + minor * cos(v)) * cos(u);
	float y = (major + minor * cos(v)) * sin(u);
	float z = minor * sin(v);
	return vec3(x, y, z);
}
