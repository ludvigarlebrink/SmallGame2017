#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "MeshImporter.h"
#include "Box.h"
#include "AShader.h"
#include "Sprite.h"
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
	glm::vec2 GetPosition(); 
	glm::vec2 GetScale();

private:
	Box m_boundingBox;
	Mesh m_playerMesh;
	TimeManager* m_time;
	MeshImporter m_meshImp;
	Transform m_transf;
	Camera m_cam;
	AShader m_shader;
	AShader m_toonShader;
	Sprite m_playerSprite;
	GLfloat m_scaleX;
	GLfloat m_scaleY;
	b2World* m_world;
	GLfloat m_posX;
	Transform m_transform;
	GLfloat m_posY;
	bool m_isMidAir;
	AShader m_spriteShader;

};

#endif