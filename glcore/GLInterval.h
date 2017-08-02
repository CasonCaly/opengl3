#ifndef GLInterval_h
#define GLInterval_h
#include "GLCore.h"
#include "math/Vector.hpp"

struct GLCORE GLInterval {
	ivec2 divisions;
	vec2 upperBound;
	vec2 textureCount;
};

#endif