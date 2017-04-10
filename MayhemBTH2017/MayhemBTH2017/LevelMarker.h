#ifndef __LEVELMARKER_H__
#define __LEVELMARKER_H__


#include "Transform.h"
#include "AShader.h"
#include "Timer.h"
#include "TextureImporter.h"
#include "Texture.h"
#include "Mesh.h"


#include <cstdint>
#include <math.h>
#include <glm.hpp>

enum MarkerMode
{
	NORMAL = 0,
	ADD_BLOCK,
	ADD_BLOCK_DRAG,
	REMOVE_BLOCK,
	REMOVE_BLOCK_DRAG,
	ADD_SPAWN_POINT
};

class LevelMarker
{
public:
	LevelMarker();
	virtual ~LevelMarker();

	void SetMarkerMode();
	void MoveUp(float speed);
	void MoveRight(float speed);

	void Update();
	void Render();

private:
	glm::vec2			m_position;

	AShader				m_green;
	uint32_t			m_currentPosX;
	uint32_t			m_currentPosY;
	uint32_t			m_savedPosX;
	uint32_t			m_savedPosY;
	Transform			m_transform;
	Camera				m_camera;
	Mesh				m_mesh;

	Timer				m_timer;
	TextureImporter		m_textureTemp;
	Texture				m_texture;

	uint32_t			m_mode;
};


#endif // __LEVELMARKER_H__