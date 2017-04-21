#ifndef _COLLIDER2D_H__
#define _COLLIDER2D_H__


#define BUFFER_OFFSET(i) ((char *)nullptr + (i))
#include "AShader.h"
#include <glm.hpp>
#include <box2d.h>

#include <glew.h>
#include "Level.h"
#include "Mesh.h"
#include "LevelImporter.h"


class Collider2D
{
public:
	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;
	Collider2D();
	virtual ~Collider2D();
	void SetBoxCollider(glm::vec2 min, glm::vec2 max);
	void CreateBoundingBoxes();
	void DrawCollider(Camera camera);
	void ImportLevel(Level level);
	bool GetPlayerCollision(int x, int y);
private:
	bool m_playerCollision[SIZE_X][SIZE_Y];
	GLuint		m_grid[SIZE_X][SIZE_Y];
	Vertex3D*	m_vertices;
	Mesh		m_mesh;
	glm::vec2	m_min;
	glm::vec2	m_max;
	glm::vec2	m_verts[4];
	GLuint		m_positionID;
	GLuint		m_bufferID;
	GLuint		m_vao;
	AShader		m_shader;
	LevelImporter m_imp;
	Transform	m_transform;
	Camera		m_camera;
	Level		m_level;
};

#endif // !_COLLIDER2D_H__
