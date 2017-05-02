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
	enum PlayerAnimState
	{
		WALK,
		RUN,
	};

	//::.. CONSTRUCTORS ..:://
	PlayerPrefab();
	PlayerPrefab(Prefab * weapon);
	virtual ~PlayerPrefab();

	void Update(float x, float y);
	void Render(Camera& cam);

	//::.. GET FUNCTIONS ..:://
	Prefab * GetPlayerPrefab();

	//::.. SET FUNCTIONS ..:://
	void SetWeapon(Prefab * weapon);

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
};


#endif // !__PLAYERPREFAB_H__