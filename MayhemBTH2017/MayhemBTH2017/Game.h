#ifndef __GAME_H__
#define __GAME_H__

#include "Level.h"
#include "LevelEditor.h"
#include "Mesh.h"
#include "MeshImporter.h"
#include "AShader.h"
#include "TimeManager.h"
#include "ParticleSystem.h"
#include "Collider2D.h"
class Game
{
public:
	Game();
	virtual ~Game();
	void Update(Camera cam);
	void Render();
	glm::vec3 GetPlayerPos();
	void SetPlayerCollision(bool* collision);
private:
private:
	MeshImporter meshImp;
	TimeManager * time;
	ParticleSystem m_particles;
	Collider2D collider;
	Transform tran;
	GLfloat pos = 0;
	InputManager* m_input;
	int posX = 42;
	AShader m_toonShader;
	Mesh m_player;
	Level m_level;
	Vertex3D m_vertices[6];
	bool m_playerCollision[84][48];
public:

private:
public:

};

#endif __GAME_H__
