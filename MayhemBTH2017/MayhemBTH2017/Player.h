#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "PrefabManager.h"
#include "Box.h"
#include "AShader.h"
#include "InputManager.h"
#include "TimeManager.h"

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

private:
private:
	Box m_boundingBox;
	Prefab * m_playerPrefab;
	Sprite m_playerSprite;
	Transform m_transf;
	Camera m_cam;
	AShader m_shader;
	AShader m_toonShader;
	bool	m_isMidAir;
	float	m_jumpTimer = 0.0f;
	b2FixtureDef m_fixture;

};

#endif