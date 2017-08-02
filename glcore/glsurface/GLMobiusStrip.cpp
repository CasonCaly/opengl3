//
//  GLCone.cpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#include "GLMobiusStrip.h"

GLMobiusStrip::GLMobiusStrip(float scale, ivec2 division) : m_scale(scale)
{
	GLInterval interval = { division, vec2(TwoPi, TwoPi), vec2(30, 20) };
    this->setInterval(interval);
}

vec3 GLMobiusStrip::evaluate(const vec2& domain)
{
	float u = domain.x;
	float t = domain.y;
	float major = 1.25;
	float a = 0.125f;
	float b = 0.5f;
	float phi = u / 2;

	// General equation for an ellipse where phi is the angle
	// between the major axis and the X axis.
	float x = a * cos(t) * cos(phi) - b * sin(t) * sin(phi);
	float y = a * cos(t) * sin(phi) + b * sin(t) * cos(phi);

	// Sweep the ellipse along a circle, like a torus.
	vec3 range;
	range.x = (major + x) * cos(u);
	range.y = (major + x) * sin(u);
	range.z = y;
	return range * m_scale;
}
