//
//  GLCone.cpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLKleinBottle.h"

GLKleinBottle::GLKleinBottle(float scale, ivec2 division):m_scale(scale)
{
	GLInterval interval = { division, vec2(TwoPi, TwoPi), vec2(30, 20) };
    this->setInterval(interval);
}

vec3 GLKleinBottle::evaluate(const vec2& domain)
{
	float v = 1 - domain.x;
	float u = domain.y;

	float x0 = 3 * cos(u) * (1 + sin(u)) +
		(2 * (1 - cos(u) / 2)) * cos(u) * cos(v);

	float y0 = 8 * sin(u) + (2 * (1 - cos(u) / 2)) * sin(u) * cos(v);

	float x1 = 3 * cos(u) * (1 + sin(u)) +
		(2 * (1 - cos(u) / 2)) * cos(v + Pi);

	float y1 = 8 * sin(u);

	vec3 range;
	range.x = u < Pi ? x0 : x1;
	range.y = u < Pi ? -y0 : -y1;
	range.z = (-2 * (1 - cos(u) / 2)) * sin(v);
	return range * m_scale;
}

bool GLKleinBottle::invertNormal(const vec2& domain)
{
	return domain.y > 3 * Pi / 2;
}