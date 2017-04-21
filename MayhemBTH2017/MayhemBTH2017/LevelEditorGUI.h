#ifndef __LEVELEDITORGUI_H__
#define __LEVELEDITORGUI_H__

#include "UIImage.h"
#include "InputManager.h"

class LevelEditorGUI
{
public:
	LevelEditorGUI();
	virtual ~LevelEditorGUI();

	//::.. GET FUNCTIONS ..:://
	bool GetMenuClosed();

	//::.. SET FUNCTIONS ..:://
	void SetMenuClosed(bool value);

	//::.. UPDATE FUNCTIONS ..:://
	void Render();

private:

	void Input();

private:

	static const int NUM_SELECTIONS = 4;

	UIImage m_closedMenu; // Merge these two menus, change texture
	UIImage m_blockMenu;
	UIImage m_blockArray[NUM_SELECTIONS];

	InputManager*	m_input;

	uint32_t m_nSize;
	uint32_t m_hSize;
	uint32_t m_pos;

	bool m_menuClosed;

};

#endif