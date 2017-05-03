#ifndef __PLAYERPREFAB_H__
#define __PLAYERPREFAB_H__


#include "PrefabManager.h"
#include "AnimController.h"
#include "glm.hpp"
#include "GLM\gtc\quaternion.hpp"
#include "Camera.h"


class PlayerPrefab
{
public:
	struct PlayerAnim
	{
		bool fullBody;
	};

	enum PlayerAnimState
	{
		RUN = 0,
		AIR,
		LAND,
		DEATH_SHOTGUN,
	};

	//::.. CONSTRUCTORS ..:://
	PlayerPrefab();
	PlayerPrefab(Prefab * weapon);
	virtual ~PlayerPrefab();

	void Update(float x, float y, float speed);
	void Render(Camera& cam);

	//::.. GET FUNCTIONS ..:://
	Prefab * GetPlayerPrefab();

	//::.. SET FUNCTIONS ..:://
	void SetWeapon(Prefab * weapon);
	void SetAnimState(uint32_t playerAnimState);

private:
	void Init(Prefab * weapon);
	void Free();

private:
	Prefab *	m_player;
	Prefab *	m_weapon;

	KeyFrame *	m_kf;
	KeyFrame *	m_keyUp;
	KeyFrame *	m_keyBase;
	KeyFrame *	m_keyDown1;
	KeyFrame *	m_keyDown2;

	float		m_y;
	float		m_x;

	float		weapRotY = 0.0f;
};


#endif // !__PLAYERPREFAB_H__