//
//  GLCone.hpp
//  glcore
//
//  Created by zhuang yusong on 2017/6/11.
//  Copyright © 2017年 zhuang yusong. All rights reserved.
//

#ifndef GLKleinBottle_hpp
#define GLKleinBottle_hpp

#include "glsurface/GLSurface.h"

class GLCORE GLKleinBottle : public GLSurface
{
public:
    
	GLKleinBottle(float scale, ivec2 division);
    
    vec3 evaluate(const vec2& domain);
    
	bool invertNormal(const vec2& domain);

private:
    
	float m_scale;
};

#endif /* GLCone_hpp */
