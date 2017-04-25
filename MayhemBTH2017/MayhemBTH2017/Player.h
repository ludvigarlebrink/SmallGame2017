#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "MeshImporter.h"
#include "Box.h"
#include "AShader.h"
#include "InputManager.h"
#include "TimeManager.h"

class Player
{
public:
	Player();
	Player(b2World* world, glm::vec2 pos, glm::vec2 scale);
	virtual ~Player();
	void Init(b2World* world, glm::vec2 pos, glm::vec2 scale);
	void Render(Transform transform, Camera camera);
	void Update();
	Box GetBox();

private:
	Box m_boundingBox;
	Mesh m_playerMesh;
	MeshImporter m_meshImp;
	Transform m_transf;
	Camera m_cam;
	AShader m_shader;
	AShader m_toonShader;
	bool	m_isMidAir;
	float	m_jumpTimer;

};

#endif