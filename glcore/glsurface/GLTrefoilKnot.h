//
//  GLCone.hpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLTrefoilKnot_hpp
#define GLTrefoilKnot_hpp

#include "glsurface/GLSurface.h"

class GLCORE GLTrefoilKnot : public GLSurface
{
public:
    
	GLTrefoilKnot(float scale, ivec2 division);
    
    vec3 evaluate(const vec2& domain);
    
private:
	float m_scale;
};

#endif /* GLCone_hpp */
