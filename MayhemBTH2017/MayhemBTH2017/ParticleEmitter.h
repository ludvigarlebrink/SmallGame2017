#ifndef _PARTICLEEMITTER_H__
#define _PARTICLEEMITTER_H__

#include "Camera.h"
#include "ParticleSystem.h"
class ParticleEmitter
{
public:
	ParticleEmitter(ParticleSystem particleSystem);
	ParticleEmitter();
	virtual ~ParticleEmitter();
	void Emit();
private:
	GLfloat m_timer = 0;
	const static int m_nrof = 10;
	ParticleSystem m_particleSystem[m_nrof];
	Camera m_camera;
public:
	void SetParticleSystem(ParticleSystem m_particleSystem);
};

#endif 
