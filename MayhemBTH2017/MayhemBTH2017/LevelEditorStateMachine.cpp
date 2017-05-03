#include "LevelEditorStateMachine.h"



LevelEditorStateMachine::LevelEditorStateMachine()
{
	//	m_width = 1920;
	//	m_height = 1080;

	m_input = InputManager::Get();

	Init();
}


LevelEditorStateMachine::~LevelEditorStateMachine()
{
	// Do nothing...
}

int32_t LevelEditorStateMachine::GetState()
{
	return m_state;
}

void LevelEditorStateMachine::SetState(int32_t state)
{
	m_state = state;
}

void LevelEditorStateMachine::Render(Camera& cam)
{
	switch (m_state)
	{
	case GUI_CLOSED:
		//RenderIcons(GUI_CLOSED);
		break;

	case GUI_BLOCK:
		Input();
		RenderIcons(GUI_BLOCK);
		break;

	case GUI_PROP:
		Input();
		RenderIcons(GUI_PROP);

		m_propPlacer.Update(m_pos);
		m_propPlacer.Render(cam);
		
		
		break;

	case GUI_BACKGROUND:
		Input();
		RenderIcons(GUI_BACKGROUND);
		break;
	}
}

void LevelEditorStateMachine::RenderIcons(size_t gui)
{

	for (int i = 0; i < m_gui[gui].m_numIcons; i++)
	{
		//m_gui[gui].m_icons[i].RenderWithUV();
		m_gui[gui].m_icons[i].RenderWithUV();
	}
	m_gui[gui].m_text.Render();
}


void LevelEditorStateMachine::Init()
{

	m_nSize = 40;
	m_hSize = 50;
	m_pos = 0;

	m_state = GUI_CLOSED;

	// Init text
	for (int i = 0; i < GUI_NUM; i++)
	{
		m_gui[i].m_text.SetSize(80);
		m_gui[i].m_text.SetPosition(-430, 320);
		m_gui[i].m_text.SetFont(".\\Assets\\Fonts\\steelfish.ttf");
		m_gui[i].m_text.SetPivot(UIText::CENTER);
		m_gui[i].m_text.SetColor(255, 255, 255, 255);

		switch (i)
		{
		case GUI_CLOSED:
			m_gui[GUI_CLOSED].m_text.SetText("");
			break;

		case GUI_BLOCK:
			m_gui[GUI_BLOCK].m_text.SetText("BLOCKS");
			m_gui[GUI_BLOCK].m_texture.SetTexture(".\\Assets\\Sprites\\textureMap.png");
			m_gui[GUI_BLOCK].m_numIcons = 8;
			break;

		case GUI_PROP:
			m_gui[GUI_PROP].m_text.SetText("PROPS");
			m_gui[GUI_PROP].m_texture.SetTexture(".\\Assets\\Sprites\\stone.jpg");
			m_gui[GUI_PROP].m_numIcons = 5;
			break;

		case GUI_BACKGROUND:
			m_gui[GUI_BACKGROUND].m_text.SetText("BACKGROUNDS");
			m_gui[GUI_BACKGROUND].m_numIcons = 12;
			break;
		}
	}

	// Init icons
	for (int guiIndex = GUI_OPEN + 1; guiIndex < GUI_NUM; guiIndex++)
	{
		m_offsetX = 50;
		m_offsetY = 50;
		m_offsetMother = 3;
		m_offsetCounter = 0;

		m_rows = -480;
		m_columns = 230;

		for (int iconIndex = 0; iconIndex < m_gui[guiIndex].m_resolution; iconIndex++)
		{
			m_gui[guiIndex].m_icons[iconIndex].SetSize(m_nSize, m_nSize);
			m_gui[guiIndex].m_icons[iconIndex].SetPosition(m_rows, m_columns);
			m_rows += m_offsetX;
			++m_offsetCounter;

			if (m_offsetCounter == m_offsetMother)
			{
				m_columns -= 50;
				m_rows = -480;
				m_offsetCounter = 0;
			}

			m_gui[guiIndex].m_icons[iconIndex].SetTexture(m_gui[guiIndex].m_texture.GetTexture());
			m_gui[guiIndex].m_icons[iconIndex].SetUV(m_gui[guiIndex].m_iconUV);
			++m_gui[guiIndex].m_iconUV.x;

			if (m_gui[guiIndex].m_iconUV.x == 16)
				++m_gui[guiIndex].m_iconUV.y;

		}
	}

	m_gui[GUI_BLOCK].m_icons[m_pos].SetSize(m_hSize, m_hSize);
}

void LevelEditorStateMachine::Input()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_pos - m_offsetMother >= 0)
		{
			m_gui[m_state].m_icons[m_pos].SetSize(m_nSize, m_nSize);
			m_pos -= m_offsetMother;
			m_gui[m_state].m_icons[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{

		if (m_pos + m_offsetMother < m_gui[m_state].m_numIcons)
		{
			m_gui[m_state].m_icons[m_pos].SetSize(m_nSize, m_nSize);
			m_pos += m_offsetMother;
			m_gui[m_state].m_icons[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	{
		if (m_pos - 1 >= 0)
		{
			m_gui[m_state].m_icons[m_pos].SetSize(m_nSize, m_nSize);
			--m_pos;
			m_gui[m_state].m_icons[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		if (m_pos + 1 < m_gui[m_state].m_numIcons)
		{
			m_gui[m_state].m_icons[m_pos].SetSize(m_nSize, m_nSize);
			++m_pos;
			m_gui[m_state].m_icons[m_pos].SetSize(m_hSize, m_hSize);
		}
	}

	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_RIGHTBUTTON))
	{
		if (m_state + 2 <= GUI_NUM)
		{
			for (int i = 0; i < m_gui[m_state].m_numIcons; i++)
			{
				m_gui[m_state].m_icons[m_pos].SetSize(m_nSize, m_nSize);
			}

			++m_state;
			if (m_pos >= m_gui[m_state].m_numIcons)
			{
				m_pos = 0;
			}
			m_gui[m_state].m_icons[m_pos].SetSize(m_hSize, m_hSize);
		}
	}

	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_LEFTBUTTON))
	{
		if (m_state - 2 > GUI_CLOSED || m_state - 1 != GUI_OPEN)
		{

			for (int i = 0; i < m_gui[m_state].m_numIcons; i++)
			{
				m_gui[m_state].m_icons[m_pos].SetSize(m_nSize, m_nSize);
			}

			--m_state;

			if (m_pos >= m_gui[m_state].m_numIcons)
			{
				m_pos = 0;
			}
			m_gui[m_state].m_icons[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
}