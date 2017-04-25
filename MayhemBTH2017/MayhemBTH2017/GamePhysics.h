#ifndef __GAMEPHYSICS_H__
#define __GAMEPHYSICS_H__

#include "BasicGun.h"
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
	GLfloat m_jumpTimer=0.0f;
	bool m_isMidAir;
	GLfloat m_tempX;
	GLfloat m_tempY;
	GLfloat m_scaleX;
	GLfloat m_scaleY;
	Sprite m_playerSprite;
	Sprite m_bazookaSprite;
	Transform m_transform;
	Collider2D m_collision;
	Sprite		m_firesprites[10];
	BasicGun	m_gun;
	Sprite		m_shot;



};

#endif // !__GAMEPHYSICS_H__