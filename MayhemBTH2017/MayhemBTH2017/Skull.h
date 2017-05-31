#ifndef __SKULL_H__
#define __SKULL_H__


#include "PrefabManager.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include "Sprite.h"

struct skullStruct : public Collidable
{
	Box skullBox;
	Prefab * skullPrefab;
	uint32_t skullID;
	bool	 collided;
};

class Skull
{
public:
	Skull();
	virtual ~Skull();

	void Update(Player & player);
	void Render(Camera & camera);



	void SetCollision(bool player = false);

private:
	std::vector<skullStruct*>	m_skull;
	uint32_t					m_skullID = 0;
	int32_t						m_collidedSkullID;

	bool		m_dead;
	bool		m_skullSpawn;
	uint32_t	m_skullTimer = 0;
	b2Vec2		m_deathPos;
	b2Filter	m_skullFilter;
	bool		m_collidedPlayer;
	Sprite		m_sprite;
	UIImage		m_yolo;


	enum _entityCategory {
		BOUNDARY = 0x0001,
		POWERUP = 0x0002,
		PLAYER1 = 0x0004,
		PLAYER3 = 0x0008,
		PLAYER2 = 0x0010,
		PLAYER4 = 0x0020,
		PROJECTILE1 = 0x0040,
		PROJECTILE2 = 0x0080,
		PROJECTILE3 = 0x0100,
		PROJECTILE4 = 0x0120,
		SKULL = 0x0140,
	};

};

#endif // !__SKULL_H__