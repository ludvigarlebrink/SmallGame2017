#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "PrefabManager.h"
#include "Box.h"
#include "AShader.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "PlayerPrefab.h"

class Player
{
public:
	//::.. CONSTRUCTORS ..:://
	Player();
	Player(b2World* world, glm::vec2 pos, glm::vec2 scale);
	virtual ~Player();

	//::..INITIALIZER..:://
	void Init(b2World* world, glm::vec2 pos, glm::vec2 scale);
	
	//::..RENDER..:://
	void Render(Camera camera);
	void Update();

	//::..SETTERS..:://
	void SetCategoryBits(short CATEGORY);
	void SetMaskBits(short MASK);
	
	//::..GETTERS..:://
	uint16 GetCategoryBits();
	uint16 GetMaskBits();
	Box GetBox();
	PlayerPrefab* GetPrefab();
	b2Fixture* GetFilter();
	void StartContact();
	void EndContact();

private:
private:
	b2Fixture* m_filter;
	Box m_boundingBox;
	PlayerPrefab * m_playerPrefab;
	Sprite m_playerSprite;
	Transform m_transf;
	Camera m_cam;
	AShader m_shader;
	AShader m_toonShader;
	bool	m_isMidAir;
	bool m_doubleJump;
	bool m_contact;
	b2FixtureDef m_fixture;
	enum _entityCategory {
		BOUNDARY = 0x0001,
		PLAYER = 0x0002,
		PROJECTILE = 0x0004,
		FRIENDLY_AIRCRAFT = 0x0008,
		ENEMY_AIRCRAFT = 0x0010,
	};
};

#endif