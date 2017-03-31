#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

//#include "MemoryManager.h"
//#include "StackAllocator.h"

#include <glew.h>
#include <SDL.h>
#include <glm.hpp>

#include "Vector.h"
#include "MasterShader.h"

class ParticleSystem: public AShader
{
public:
	//::..CONSTRUCTORS..:://
	ParticleSystem();
	
	//Destructor
	virtual ~ParticleSystem();

	//::..HELPER FUNCTIONS..:://

	void Update();
	void Render(GLuint dt, const glm::mat4());
	
private:
	//::..HELPER FUNCTIONS..:://
	void AddAttributeLocation();
private:
	bool m_

};

#endif
