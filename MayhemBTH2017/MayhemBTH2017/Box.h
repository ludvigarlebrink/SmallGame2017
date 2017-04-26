#ifndef __BOX_H__
#define __BOX_H__

#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Mesh.h"

class Box
{
public:
	Box();
	virtual ~Box();

	void initDynamic(b2World* world, const glm::vec2& pos, const glm::vec2& scale);
	void initStatic(b2World* world, const glm::vec2& pos, const glm::vec2& scale);

	//::.. GET FUNCTIONS ..:://
	b2Body* getBody() { return this->body; }
	b2Fixture* getFixture() { return this->fixture; }
	glm::vec2 getScale() { return this->m_scale; }

private:
	b2Body* body = nullptr;
	b2Fixture* fixture;

	glm::vec2 m_scale;

};

#endif