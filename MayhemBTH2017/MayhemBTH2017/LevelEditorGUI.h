#ifndef __LEVELEDITORGUI_H__
#define __LEVELEDITORGUI_H__

#include "UIImage.h"
#include "UIText.h"
#include "InputManager.h"
#include <fstream>

enum GUI
{
	CLOSED_MENU = 0,
	BLOCK_MENU,
	PROP_MENU,
	BACKGROUND_MENU,
	NUM_MENUS
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
	void RenderArray(UIImage menu_array[], int num_array);

private:

	void Input();

private:


	static const int NUM_BLOCKS = 4;
	static const int NUM_PROPS = 4;
	static const int NUM_BACKGROUNDS = 4;

	UIImage m_closedMenu; // Merge these two menus, change texture
	UIImage m_blockMenu;

	UIImage m_blockArray[NUM_BLOCKS];
	UIImage m_propArray[NUM_PROPS];
	UIImage m_backgroundArray[NUM_BACKGROUNDS];

	UIText m_text;

	InputManager*	m_input;

	uint32_t m_nSize;
	uint32_t m_hSize;
	int32_t m_state;
	int32_t m_pos;

	std::ifstream m_texFile;
	std::string m_line;
	uint32_t m_index;

};

#endif