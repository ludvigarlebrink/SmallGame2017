#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "InputManager.h"
#include "Level.h"
#include "Timer.h"
#include "TextureImporter.h"

#include <glm.hpp>
#include <cstdint>


class LevelEditor
{
public:
	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;

	//::.. CONSTRUCTORS ..:://
	LevelEditor();
	virtual ~LevelEditor();

	//::.. UPDATE FUNCTIONS ..:://
	void Update();

private:
	//::.. HELP FUNCTIONS ..:://
	void AxisMove();
	void ButtonInput();
	void ClampPos();
	void RenderSelector();

private:
	InputManager *		m_input;	

	Level				m_level;

	AShader				m_green;
	uint32_t			m_currentPosX;
	uint32_t			m_currentPosY;
	uint32_t			m_savedPosX;
	uint32_t			m_savedPosY;
	Transform			m_transform;
	Camera				m_camera;
	Mesh				m_mesh;

	Timer				m_timer;
	TextureImporter		texImp;
	Texture				m_texture;
};

#endif // __LEVELEDITOR_H__