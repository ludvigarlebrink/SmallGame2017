#pragma once
#include <Box2D\Box2D.h>
#include "Box.h"
#include "Collider2D.h"
#include "Player.h"
#include "TimeManager.h"
class GamePhysics
{
public:
	GamePhysics();
	virtual ~GamePhysics();
	void enterWorld();
	void Update(Transform transform);
	void Render(Transform &transform, Camera camera);
	glm::vec3 GetPosition();

private:
	std::unique_ptr<b2World> m_world;
	Box m_newBox;
	Box m_newBox2;
	Player m_player;
	TimeManager* m_time;
	GLfloat m_tempX;
	GLfloat m_tempY;
	GLfloat m_scaleX;
	GLfloat m_scaleY;
	Sprite m_playerSprite;
	Transform m_transform;
	Collider2D m_collision;



};

