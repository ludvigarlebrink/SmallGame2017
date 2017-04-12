#include "Box.h"



Box::Box()
{
	m_shader = new AShader("leo", false, false);
}


Box::~Box()
{
}

void Box::Init(b2World * world, const glm::vec2 & pos, const glm::vec2 & dim)
{
	this->m_dim = dim;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);

	this->body = world->CreateBody(&bodyDef);

	b2PolygonShape boxshape;

	boxshape.SetAsBox(dim.x / 2.0f, dim.y / 2.0f);

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &boxshape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	this->fixture = this->body->CreateFixture(&fixtureDef);

	this->verts[0] = glm::vec2(this->body->GetPosition().x, this->body->GetPosition().y);

	this->verts[1] = glm::vec2(this->body->GetPosition().x + dim.x, this->body->GetPosition().y);

	this->verts[2] = glm::vec2(this->body->GetPosition().x, this->body->GetPosition().y + dim.y);

	this->verts[3] = glm::vec2(this->body->GetPosition().x + dim.x, this->body->GetPosition().y + dim.y);

	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(this->verts[0]), &this->verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

b2Body * Box::GetBody()
{
	return this->body;
}

b2Fixture * Box::GetFixture()
{
	return this->fixture;
}

void Box::draw()
{
	m_shader->Bind();

	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Box::update(glm::vec2 pos)
{
	this->verts[0] = glm::vec2(this->body->GetPosition().x, this->body->GetPosition().y);

	this->verts[1] = glm::vec2(this->body->GetPosition().x + this->m_dim.x, this->body->GetPosition().y);

	this->verts[2] = glm::vec2(this->body->GetPosition().x, this->body->GetPosition().y + this->m_dim.y);

	this->verts[3] = glm::vec2(this->body->GetPosition().x + this->m_dim.x, this->body->GetPosition().y + this->m_dim.y);
}
