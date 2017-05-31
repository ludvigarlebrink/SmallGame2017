
#ifndef __PARTICLE_H__
#define __PARTICLE_H__


#include <glew.h>
#include <SDL.h>
#include <glm.hpp>

#include "Vector.h"
#include "Ashader.h"
#include "Mesh.h"


struct Particle {
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec4 color;
	GLfloat life;
	GLfloat size;


};




#endif