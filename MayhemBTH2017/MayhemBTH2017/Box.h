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

	void InitDynamic(b2World* world, const glm::vec2& pos, const glm::vec2& scale);

	void InitStatic(b2World* world, const glm::vec2& pos, const glm::vec2& scale);

	b2Body* getBody() { return m_body; }
	b2Fixture* getFixture() { return m_fixture; }

	glm::vec2 getScale() { return m_scale; }
	void SetCategoryBits(short CATEGORY);
	void SetMaskBits(short MASK);
	uint16 GetCategoryBits();
	uint16 GetMaskBits();




private:
	b2Body* m_body = nullptr;
	b2Fixture* m_fixture;
	b2FixtureDef m_fixtureDef;
	glm::vec2 m_scale;

};

