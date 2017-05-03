#ifndef __LEVELEDITORGUI_H__
#define __LEVELEDITORGUI_H__

#include "UIImage.h"
#include "UIText.h"
#include "InputManager.h"
#include <fstream>
#include <vector>

struct GUI
{
	glm::vec2				m_iconUV = glm::vec2(0, 0);
	static const int32_t	m_resolution = 256;
	int32_t					m_numIcons = 0;
	UIText					m_text;
	UIImage					m_texture;
	UIImage					m_icons[m_resolution];
};

enum GUIState
{
	GUI_CLOSED = 0,
	GUI_OPEN,
	GUI_BLOCK,
	GUI_PROP,
	GUI_BACKGROUND,
	GUI_NUM
};

class LevelEditorGUI
{
public:
	LevelEditorGUI();
	virtual ~LevelEditorGUI();

	//::.. GET FUNCTIONS ..:://
	int32_t GetState();

	//::.. SET FUNCTIONS ..:://
	void SetState(int32_t state);

	//::.. UPDATE FUNCTIONS ..:://
	void Render();
	void RenderIcons(size_t gui);

private:

	void Init();
	void Input();

private:

	GUI				m_gui[GUI_NUM];
	InputManager*	m_input;

	uint32_t		m_nSize;
	uint32_t		m_hSize;
	int32_t			m_state;
	int32_t			m_pos;

	int32_t			m_rows;
	int32_t			m_columns;
	int32_t			m_offsetX;
	int32_t			m_offsetY;
	int32_t			m_offsetMother;
	int32_t			m_offsetCounter;
};

#endif