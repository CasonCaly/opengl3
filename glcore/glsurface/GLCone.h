//
//  GLCone.hpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLCone_hpp
#define GLCone_hpp

#include "glsurface/GLSurface.h"

class GLCORE GLCone : public GLSurface
{
public:
    
	GLCone(float height, float radius, ivec2 division);
    
    vec3 evaluate(const vec2& domain);
    
private:
    
    float m_height;
    
    float m_radius;
};

#endif /* GLCone_hpp */
