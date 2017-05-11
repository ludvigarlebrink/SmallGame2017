#pragma once
#include "ParticleSystem.h"
#include "AShader.h"
class ParticleTest
{
public:
	ParticleTest();
	void Render();
	~ParticleTest();
private:
	ParticleSystem m_particles;
	AShader drawShader;
};

