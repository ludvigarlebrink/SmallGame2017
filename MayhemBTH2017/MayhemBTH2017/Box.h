#ifndef __BOX_H__
#define __BOX_H__



#include <box2d.h>
#include <glm.hpp>
#include <glew.h>

#include "AShader.h"

class Box
{
public:
	Box();
	virtual ~Box();

	void Init(b2World* world, const glm::vec2& pos, const glm::vec2& dim);

	b2Body* GetBody();
	b2Fixture* GetFixture();

	void draw();

	void update(glm::vec2 pos);

private:
	b2Body* body;
	b2Fixture* fixture;

	glm::vec2 verts[4];
	glm::vec2 m_dim;

	GLuint textureID;
	GLuint texLoc;
	GLuint bufferID;

	AShader* m_shader;

};

#endif // !__BOX_H__
