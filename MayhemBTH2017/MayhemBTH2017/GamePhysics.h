#ifndef __GAMEPHYSICS_H__
#define __GAMEPHYSICS_H__


#include "Collider2D.h"
#include "Player.h"
#include "Weapon.h"


class GamePhysics
{
public:

	GamePhysics();
	virtual ~GamePhysics();
	void EnterWorld();
	void Update();
	void Render(Camera camera);
	glm::vec3 GetPosition();

private:
	std::unique_ptr<b2World> m_world;
	Box m_newBox;
	Box m_newBox2;
	Box m_powerUpBox;
	Player m_player;
	Collider2D gameFloor;

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
	Collider2D m_floorCollider;
	Sprite		m_firesprites[10];
	Sprite		m_shot;
	//Temporary
	b2FixtureDef powerUpFixture;

	Weapon m_weapon;


};

#endif // !__GAMEPHYSICS_H__