//
//  GLCone.hpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLTorus_hpp
#define GLTorus_hpp

#include "glsurface/GLSurface.h"

class GLCORE GLTorus : public GLSurface
{
public:
    
	GLTorus(float majorRadius, float minorRadius, ivec2 division);
    
    vec3 evaluate(const vec2& domain);
    
private:
	float m_majorRadius;
	float m_minorRadius;
};

#endif /* GLCone_hpp */
