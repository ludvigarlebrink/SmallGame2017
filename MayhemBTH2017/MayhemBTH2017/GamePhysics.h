#ifndef __GAMEPHYSICS_H__
#define __GAMEPHYSICS_H__

#include "AProjectile.h"
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
	Box m_powerUpBox;
	Player m_player;

	TimeManager* m_time;
	GLfloat m_jumpTimer=0.0f;
	bool m_isMidAir;
	GLfloat m_playerScaleX;
	GLfloat m_playerScaleY;
	GLfloat m_playerPosX;
	GLfloat m_playerPosY;

	GLfloat m_powerUpScaleX;
	GLfloat m_powerUpScaleY;
	GLfloat m_powerUpPosX;
	GLfloat m_powerUpPosY;

	Sprite m_playerSprite;
	Sprite m_powerUpSprite;
	Transform m_transform;
	Collider2D m_collision;
	Sprite		m_firesprites[10];
	short CATEGORY_PLAYER = 0x0001;  // 0000000000000001 in binary
	short CATEGORY_MONSTER = 0x0002; // 0000000000000010 in binary
	short CATEGORY_POWERUP = 0x0004; // 0000000000000100 in binary
	Sprite		m_shot;
	//Temporary
	b2FixtureDef powerUpFixture;


};

#endif // !__GAMEPHYSICS_H__