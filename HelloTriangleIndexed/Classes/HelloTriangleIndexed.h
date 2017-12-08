#ifndef HELLO_CONE_H
#define HELLO_CONE_H
#include <vector>
using namespace std;
#include "glclass/GLApp.h"
#include "glclass/GLBuffer.h"

struct Vertex {
    vec3 Position;
    vec4 Color;
};

struct Animation {
    Quaternion Start;
    Quaternion End;
    Quaternion Current;
    float Elapsed;
    float Duration;
};

class HelloTriangleIndexed : public GLApp{
    
public:
    
    HelloTriangleIndexed();
    
    void init();
    
    void render() override;

private:
    
    GLBuffer m_VBO;
    GLBuffer m_EBO;
    
    GLAttribute m_vertexAttr;
};
#endif
