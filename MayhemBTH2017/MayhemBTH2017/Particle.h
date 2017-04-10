
#ifndef __PARTICLE_H__
#define __PARTICLE_H__


#include <glew.h>
#include <SDL.h>
#include <glm.hpp>

#include "Vector.h"
#include "Ashader.h"
#include "Mesh.h"


struct Particle {
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 color = glm::vec3(0.0, 1.0, 0.0);
	GLfloat velocity = 1.0f;
	GLfloat timeAlive = 0.0f;


};

#endif