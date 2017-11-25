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

class HelloCone : public GLApp{
    
public:
    
    HelloCone();
    
    void init();
    
    void render() override;

	void onTouchBegan(float x, float y) override;

	void onTouchMove(float x, float y) override;

	void onTouchEnd(float x, float y) override;

private:
    
    void applyOrtho(float maxX, float maxY);
    
    void applyRotation(float degrees);

private:
    
    vector<Vertex> m_cone;
    vector<Vertex> m_disk;
    Animation m_animation;
	float m_rotationAngle;
	float m_lastRotationAngle;
	float m_previousX;
	float m_previousY;

	int m_bodyIndexCount;
	int m_diskIndexCount;
	GLBuffer m_vertexBuffer;
	GLBuffer m_indexBuffer;
};
#endif
