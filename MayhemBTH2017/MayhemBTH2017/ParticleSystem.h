#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))
//#include "MemoryManager.h"
//#include "StackAllocator.h"

#include <glew.h>
#include <SDL.h>
#include <glm.hpp>

#include "Vector.h"
#include "Ashader.h"
#include "Mesh.h"
#include "ParticleTransform.h"
#include "Particle.h"

class ParticleSystem : public AShader
{
public:
	//::..CONSTRUCTORS..:://
	ParticleSystem(std::string shadername, glm::vec3 pos, glm::vec3 col);
	void UpdateParticles();

	//Destructor
	virtual ~ParticleSystem();

	//::..HELPER FUNCTIONS..:://



private:
	//::..HELPER FUNCTIONS..:://
	void AddAttributeLocation();
	void AddTimerUniform();
	void ShadersInit();
	void LoadParticleVBOS(Particle* p, GLuint nrOfVerts);
	void RenderTransformed();
	void TransformFeedbackSwap();
	glm::vec3 GetRandomDir();

private:
	Particle m_part[1];


	const uint64_t PARTICLE_COUNT = 10000;
	AShader	m_pShader;
	AShader	m_emitterShader;
	AShader m_drawShader;
	Camera	m_camera;
	GLint inputAttrib, inputAttrib2;

	glm::vec3 m_feedbackInfo[6];
	GLuint m_vao[2];
	GLuint m_buffer;
	GLuint m_drawCount;
	GLuint m_particleBufferA;
	GLuint m_particleBufferB;
	GLuint m_positionID;
	GLuint m_colorID;
	GLuint m_velocityID;
	GLuint m_timeAliveID;
	GLuint m_timerID;
	uint64_t m_offset = 0;
	GLfloat m_timer = 0.0f;
	Transform tmpTransform;
	GLuint m_drawVAO;
	GLuint testVAO;
	GLuint testBUffer;
	GLfloat info[6];
	GLuint particlePosID, particleDirID, particleColorID, particleVelocityID, particleTimeAliveID;
	GLuint inPosID, inDirID, inColID, inVelID, inTimeID;
	uint64_t offset;

};

#endif
