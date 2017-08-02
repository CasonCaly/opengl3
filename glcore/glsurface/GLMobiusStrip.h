//
//  GLCone.hpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLMobiusStrip_hpp
#define GLMobiusStrip_hpp

#include "glsurface/GLSurface.h"

class GLCORE GLMobiusStrip : public GLSurface
{
public:
    
	GLMobiusStrip(float scale, ivec2 division);
    
    vec3 evaluate(const vec2& domain);
    
private:

	float m_scale;
};

#endif /* GLCone_hpp */
