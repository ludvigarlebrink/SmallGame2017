#pragma once

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

	b2Body* getBody();
	b2Fixture* getFixture();

	glm::vec2 getScale();



private:
	b2Body* body = nullptr;
	b2Fixture* fixture;

	glm::vec2 m_scale;

};

