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

	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;

	LevelMarker();
	virtual ~LevelMarker();

	//::.. MODIFY FUNCTIONS ..:://
	void MoveUp(float speed);
	void MoveRight(float speed);

	//::.. SET FUNCTIONS ..::// //
	void SetMarkerMode(uint32_t markerMode);
	void SetCurrentPosX(uint32_t pos);
	void SetCurrentPosY(uint32_t pos);
	void SetSavedPosX(uint32_t pos);
	void SetSavedPosY(uint32_t pos);
	void SetStartX(uint32_t value);
	void SetStartY(uint32_t value);
	void SetEndX(uint32_t value);
	void SetEndY(uint32_t value);
	void SetSizeX(uint32_t value);
	void SetSizeY(uint32_t value);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetMarkerMode();
	uint32_t GetCurrentPosX();
	uint32_t GetCurrentPosY();
	uint32_t GetSavedPosX();
	uint32_t GetSavedPosY();
	uint32_t GetStartX();
	uint32_t GetStartY();
	uint32_t GetEndX();
	uint32_t GetEndY();
	uint32_t GetSizeX();
	uint32_t GetSizeY();


	//::.. UPDATE FUNCTIONS ..:://
	void Update(Camera & camera);
	void Render(Camera & camera);
	
private:
	//::.. HELP FUNCTIONS ..:://
	void ClampPos();

private:
	glm::vec2			m_position;

	AShader				m_green;
	uint32_t			m_currentPosX;
	uint32_t			m_currentPosY;
	uint32_t			m_savedPosX;
	uint32_t			m_savedPosY;
	uint32_t			startX;
	uint32_t			startY;
	uint32_t			endX;
	uint32_t			endY;
	uint32_t			sizeX;
	uint32_t			sizeY;
	Transform			m_transform;
	Mesh				m_mesh;

	TextureImporter		m_textureTemp;
	Texture				m_texture;

	uint32_t			m_mode;
};


#endif // __LEVELMARKER_H__