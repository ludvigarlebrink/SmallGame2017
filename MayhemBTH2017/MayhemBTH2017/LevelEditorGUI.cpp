#include "LevelEditorGUI.h"



LevelEditorGUI::LevelEditorGUI()
{
	//	m_width = 1920;
	//	m_height = 1080;

	m_input = InputManager::Get();

	Init();
}


LevelEditorGUI::~LevelEditorGUI()
{
	// Do nothing...
}

int32_t LevelEditorGUI::GetState()
{
	return m_state;
}

void LevelEditorGUI::SetState(int32_t state)
{
	m_state = state;
}

void LevelEditorGUI::Render()
{
	switch (m_state)
	{
	case GUI_CLOSED:
		RenderIcons(GUI_CLOSED);
		break;

	case GUI_BLOCK:
		Input();
		RenderIcons(GUI_BLOCK);
		break;

	case GUI_PROP:
		Input();
		RenderIcons(GUI_PROP);
		break;

	case GUI_BACKGROUND:
		Input();
		RenderIcons(GUI_BACKGROUND);
		break;
	}

}

void LevelEditorGUI::RenderIcons(size_t gui)
{

	if (gui != GUI_CLOSED)
		m_gui[GUI_OPEN].m_icons.at(0).Render();

	for (int i = 0; i < m_gui[gui].m_numIcons; i++)
	{
		m_gui[gui].m_icons.at(i).RenderWithUV();
	}
	m_gui[gui].m_text.Render();
}


void LevelEditorGUI::Init()
{
	m_offsetX = 50;
	m_offsetY = 50;
	m_offsetMother = 2;

	m_rows = 0;
	m_columns = 0;

	m_nSize = 50;
	m_hSize = 70;
	m_pos = 0;

	m_state = GUI_CLOSED;

	// Init text
	for (int i = 0; i < GUI_NUM; i++)
	{
		m_gui[i].m_text.SetSize(80);
		m_gui[i].m_text.SetPosition(-530, 320);
		m_gui[i].m_text.SetFont(".\\Assets\\Fonts\\steelfish.ttf");
		m_gui[i].m_text.SetPivot(UIText::LEFT);
		m_gui[i].m_text.SetColor(255, 255, 255, 255);

		switch (i)
		{
		case GUI_CLOSED:
			m_gui[GUI_CLOSED].m_text.SetText("");
			break;

		case GUI_BLOCK:
			m_gui[GUI_BLOCK].m_text.SetText("BLOCKS");
			break;

		case GUI_PROP:
			m_gui[GUI_PROP].m_text.SetText("PROPS");
			break;

		case GUI_BACKGROUND:
			m_gui[GUI_BACKGROUND].m_text.SetText("BACKGROUNDS");
			break;
		}
	}

	// Init textures
	m_texFile.open(".\\Assets\\Sprites\\GUITextures.txt");
	for (int i = 0; i < GUI_NUM; i++)
	{
		while (std::getline(m_texFile, m_line))
		{
			if (m_line == "STOP")
			{
				break;
			}

			UIImage temp;
			temp.SetTexture(m_line.c_str());
			m_gui[i].m_icons.push_back(temp);
			m_gui[i].m_numIcons++;
			//m_gui[i].m_iconUV.push_back();
		}
	}
	m_texFile.close();

	// Init icons
	for (int guiIndex = GUI_OPEN + 1; guiIndex < GUI_NUM; guiIndex++)
	{
		m_rows = 0;
		m_columns = 0;

		for (int iconIndex = 0; iconIndex < m_gui[guiIndex].m_numIcons; iconIndex++)
		{
			m_gui[guiIndex].m_icons[iconIndex].SetSize(m_nSize, m_nSize);
			m_gui[guiIndex].m_icons.at(iconIndex).SetPosition(m_rows, m_columns);

			m_rows += m_offsetX;
			if (m_rows == m_offsetX * m_offsetMother)
			{
				m_columns -= 50;
				m_rows = 0;
			}
		}
	}

	m_gui[GUI_BLOCK].m_icons.at(m_pos).SetSize(m_hSize, m_hSize);
}

void LevelEditorGUI::Input()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_pos - m_offsetMother >= 0)
		{
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_nSize, m_nSize);
			m_pos -= m_offsetMother;
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{

		if (m_pos + m_offsetMother < m_gui[m_state].m_numIcons)
		{
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_nSize, m_nSize);
			m_pos += m_offsetMother;
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_hSize, m_hSize);
		}

	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	{

		if (m_pos - 1 >= 0)
		{
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_nSize, m_nSize);
			--m_pos;
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		if (m_pos + 1 < m_gui[m_state].m_numIcons)
		{
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_nSize, m_nSize);
			++m_pos;
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_hSize, m_hSize);
		}
	}

	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_RB))
	{
		if (m_state + 2 <= GUI_NUM)
		{
			for (int i = 0; i < m_gui[m_state].m_numIcons; i++)
			{
				m_gui[m_state].m_icons.at(m_pos).SetSize(m_nSize, m_nSize);
			}

			m_state++;
			if (m_pos >= m_gui[m_state].m_numIcons)
			{
				m_pos = 0;
			}
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_hSize, m_hSize);
		}
	}

	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_LEFTSHOULDER))
	{
		if (m_state - 2 > GUI_CLOSED || m_state - 1 != GUI_OPEN)
		{

			for (int i = 0; i < m_gui[m_state].m_numIcons; i++)
			{
				m_gui[m_state].m_icons.at(m_pos).SetSize(m_nSize, m_nSize);
			}

			m_state--;
			if (m_pos >= m_gui[m_state].m_numIcons)
			{
				m_pos = 0;
			}
			m_gui[m_state].m_icons.at(m_pos).SetSize(m_hSize, m_hSize);
		}
	}
}
