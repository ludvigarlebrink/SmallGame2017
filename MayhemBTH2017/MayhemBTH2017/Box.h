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

	b2Body* getBody() { return this->body; }
	b2Fixture* getFixture() { return this->fixture; }

	glm::vec2 getScale() { return this->m_scale; }
	void SetCategoryBits(short CATEGORY);
	void SetMaskBits(short MASK);
	uint16 GetCategoryBits();
	uint16 GetMaskBits();




private:
	b2Body* body = nullptr;
	b2Fixture* fixture;
	b2FixtureDef m_fixtureDef;
	glm::vec2 m_scale;

};

