#ifndef _COLLIDER2D_H__
#define _COLLIDER2D_H__


#define BUFFER_OFFSET(i) ((char *)nullptr + (i))
#include "AShader.h"
#include <glm.hpp>
#include <box2d.h>
#include <vector>
#include <glew.h>
#include "Level.h"
#include "Mesh.h"
#include "LevelHandler.h"
#include "Box.h"
#include "Sprite.h"
#include "Texture.h"
#include "TextureHandler.h"
#include "Collidable.h"

class Collider2D : public Collidable
{
public:
	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;
	Collider2D();
	virtual ~Collider2D();
	void SetBoxCollider(glm::vec2 min, glm::vec2 max);
	void CreateBoundingBoxes(b2World* world, std::string levelName);

	void DrawCollider(Camera camera);
	void DrawColliderShadowPass(Camera camera);
	
	void ImportLevel(Level level);
	void CreatePlayerBoundingBox(b2World* world);
	uint16 GetMaskBits();
	uint16 GetCategoryBits();
	void SetMaskBits(uint16 MASK);
	void SetCategoryBits(uint16 CATEGORY);
	void StartContact();
	void EndContact();

	std::vector<Box> GetBoxes();

private:
	b2Fixture*  m_filter;
	GLuint		m_grid[SIZE_X][SIZE_Y];
	Mesh		m_mesh;
	glm::vec2	m_min;
	glm::vec2	m_max;
	glm::vec2	m_verts[4];
	GLuint		m_positionID;
	GLuint		m_bufferID;
	GLuint		m_vao;
	AShader		m_shader;
	LevelHandler m_levelImport;
	Transform	m_transform;
	Camera		m_camera;
	Level		m_level;
	Transform	m_transf;
	bool m_contact;
	Box m_gameFloor;
	std::vector<Box>	m_boxes;
	
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

	Texture	*			m_megaTexture;
	TextureHandler		m_textureTemp;
	glm::vec4 m_uv;

};

#endif // !_COLLIDER2D_H__
