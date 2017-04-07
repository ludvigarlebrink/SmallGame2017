#ifndef __LEVELMARKER_H__
#define __LEVELMARKER_H__


#include "Transform.h"
#include "AShader.h"
#include "Timer.h"
#include "TextureImporter.h"
#include "Texture.h"
#include "Mesh.h"


#include <cstdint>


class LevelMarker
{
public:
	LevelMarker();
	virtual ~LevelMarker();


private:
	// MARKER
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