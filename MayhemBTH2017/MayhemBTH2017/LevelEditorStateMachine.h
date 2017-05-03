#ifndef __LEVELEDITORSTATEMACHINE_H__
#define __LEVELEDITORSTATEMACHINE_H__


#include "UIImage.h"
#include "UIText.h"
#include "InputManager.h"
#include "LevelEditorPropPlacer.h"

#include <fstream>
#include <vector>

struct GUI
{
	UIText					m_text;
	int32_t					m_numIcons = 0;
	glm::vec2				m_iconUV[16][16];
	std::vector<UIImage>	m_icons;
};

enum LevelEditorState
{
	GUI_CLOSED = 0,
	GUI_OPEN,
	GUI_BLOCK,
	GUI_PROP,
	GUI_BACKGROUND,
	GUI_NUM
};

class LevelEditorStateMachine
{
public:
	LevelEditorStateMachine();
	virtual ~LevelEditorStateMachine();

	//::.. GET FUNCTIONS ..:://
	int32_t GetState();

	//::.. SET FUNCTIONS ..:://
	void SetState(int32_t state);

	//::.. UPDATE FUNCTIONS ..:://
	void Render(Camera& cam);
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

	std::ifstream	m_texFile;
	std::string		m_line;

	LevelEditorPropPlacer m_propPlacer;
};

#endif // !__LEVELEDITORSTATEMACHINE_H__