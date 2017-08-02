//
//  GLCone.cpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLTrefoilKnot.h"

GLTrefoilKnot::GLTrefoilKnot(float scale, ivec2 division) :m_scale(scale)
{
	GLInterval interval = { division, vec2(TwoPi, TwoPi), vec2(30, 20) };
    this->setInterval(interval);
}

vec3 GLTrefoilKnot::evaluate(const vec2& domain)
{
	const float a = 0.5f;
	const float b = 0.3f;
	const float c = 0.5f;
	const float d = 0.1f;
	float u = (TwoPi - domain.x) * 2;
	float v = domain.y;

	float r = a + b * cos(1.5f * u);
	float x = r * cos(u);
	float y = r * sin(u);
	float z = c * sin(1.5f * u);

	vec3 dv;
	dv.x = -1.5f * b * sin(1.5f * u) * cos(u) -
		(a + b * cos(1.5f * u)) * sin(u);
	dv.y = -1.5f * b * sin(1.5f * u) * sin(u) +
		(a + b * cos(1.5f * u)) * cos(u);
	dv.z = 1.5f * c * cos(1.5f * u);

	vec3 q = dv.Normalized();
	vec3 qvn = vec3(q.y, -q.x, 0).Normalized();
	vec3 ww = q.Cross(qvn);

	vec3 range;
	range.x = x + d * (qvn.x * cos(v) + ww.x * sin(v));
	range.y = y + d * (qvn.y * cos(v) + ww.y * sin(v));
	range.z = z + d * ww.z * sin(v);
	return range * m_scale;
}
