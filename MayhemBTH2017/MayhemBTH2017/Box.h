#pragma once

#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include <string>
#include "Sprite.h"

class Box
{
public:
	Box();
	virtual ~Box();

	void init(b2World* world, const glm::vec2& pos, const glm::vec2& scale);

	b2Body* getBody() { return this->body; }
	b2Fixture* getFixture() { return this->fixture; }

	glm::vec2 getScale() { return this->m_scale; }

	void setTexture(const std::string& filePath);

	void draw();

	void updateSprite(glm::vec2 pos, glm::vec2 scale);

private:
	b2Body* body = nullptr;
	b2Fixture* fixture;

	Sprite sprite;
	glm::vec2 m_scale;

};

