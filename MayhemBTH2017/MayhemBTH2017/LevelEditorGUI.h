#ifndef __LEVELEDITORGUI_H__
#define __LEVELEDITORGUI_H__

#include "UIImage.h"
#include "UIText.h"
#include "InputManager.h"
#include <fstream>
#include <vector>

struct GUI
{
	UIText m_text;
	uint32_t m_numIcons = 0;
	std::vector<UIImage> m_icons;
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

	GUI		m_gui[GUI_NUM];
	InputManager*	m_input;

	uint32_t m_nSize;
	uint32_t m_hSize;
	int32_t m_state;
	int32_t m_pos;

	int32_t	m_rows;
	int32_t m_columns;
	int32_t m_offsetX;
	int32_t m_offsetY;

	std::ifstream m_texFile;
	std::string m_line;
};

#endif