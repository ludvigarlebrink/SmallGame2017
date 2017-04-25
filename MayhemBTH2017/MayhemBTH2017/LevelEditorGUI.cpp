#include "LevelEditorGUI.h"



LevelEditorGUI::LevelEditorGUI()
{
	//	m_width = 1280;
	//	m_height = 720;

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
		m_gui[gui].m_icons.at(i).Render();
	}
	m_gui[gui].m_text.Render();
}


void LevelEditorGUI::Init()
{

	//x = -575
	//y = 175

	m_offsetX = 50;
	m_offsetY = 50;

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
	// TODO - Fix a proper SetPosition alghoritm, don't want to hardcorde them everytime we add a new GUIState
	// SetPosition is temporary hardcoded
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
			if (m_rows == m_offsetX * 2)
			{
				m_columns += 50;
				m_rows = 0;
			}

			std::cout << m_gui[guiIndex].m_icons.at(iconIndex).GetPosX() << " , " << m_gui[guiIndex].m_icons.at(iconIndex).GetPosY() << std::endl;
		}
	}

}

void LevelEditorGUI::Input()
{
	//if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	//{
	//	switch (m_state)
	//	{
	//	case GUI_BLOCK:
	//		if (m_pos - 2 >= 0)
	//		{
	//			m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
	//			m_pos -= 2;
	//			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;

	//	case GUI_PROP:
	//		if (m_pos - 2 >= 0)
	//		{
	//			m_propArray[m_pos].SetSize(m_nSize, m_nSize);
	//			m_pos -= 2;
	//			m_propArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;
	//	}

	//}
	//else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	//{

	//	switch (m_state)
	//	{
	//	case GUI_BLOCK:
	//		if (m_pos + 2 < NUM_BLOCKS)
	//		{
	//			m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
	//			m_pos += 2;
	//			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;

	//	case GUI_PROP:
	//		if (m_pos + 2 < NUM_PROPS)
	//		{
	//			m_propArray[m_pos].SetSize(m_nSize, m_nSize);
	//			m_pos += 2;
	//			m_propArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;
	//	}

	//}
	//else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	//{

	//	switch (m_state)
	//	{
	//	case GUI_BLOCK:
	//		if (m_pos - 1 >= 0)
	//		{
	//			m_gui[m_pos].SetSize(m_nSize, m_nSize);
	//			--m_pos;
	//			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;

	//	case GUI_PROP:
	//		if (m_pos - 1 >= 0)
	//		{
	//			m_propArray[m_pos].SetSize(m_nSize, m_nSize);
	//			--m_pos;
	//			m_propArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;
	//	}
	//}
	//else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	//{
	//	switch (m_state)
	//	{
	//	case GUI_BLOCK:
	//		if (m_pos + 1 < NUM_BLOCKS)
	//		{
	//			m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
	//			++m_pos;
	//			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;

	//	case GUI_PROP:
	//		if (m_pos + 1 < NUM_PROPS)
	//		{
	//			m_propArray[m_pos].SetSize(m_nSize, m_nSize);
	//			++m_pos;
	//			m_propArray[m_pos].SetSize(m_hSize, m_hSize);
	//		}
	//		break;
	//	}
	//}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_RB))
	{
		if (m_state + 2 <= GUI_NUM)
		{
			m_state++;

			for (int i = 0; i < NUM_BLOCKS; i++)
			{
				if (i != m_pos)
					m_blockArray[i].SetSize(m_nSize, m_nSize);
				else
					m_blockArray[i].SetSize(m_hSize, m_hSize);
			}

			for (int i = 0; i < NUM_PROPS; i++)
			{
				if (i != m_pos)
					m_propArray[i].SetSize(m_nSize, m_nSize);
				else
					m_propArray[i].SetSize(m_hSize, m_hSize);
			}
		}
	}

	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_LEFTSHOULDER))
	{
		if (m_state - 2 > GUI_CLOSED || m_state - 1 != GUI_OPEN)
		{
			m_state--;

			/*for (int i = 0; i < GUI_NUM; i++)
			{
				if (i != m_pos)
					m_blockArray[i].SetSize(m_nSize, m_nSize);
				else
					m_blockArray[i].SetSize(m_hSize, m_hSize);
			}

			for (int i = 0; i < NUM_PROPS; i++)
			{
				if (i != m_pos)
					m_propArray[i].SetSize(m_nSize, m_nSize);
				else
					m_propArray[i].SetSize(m_hSize, m_hSize);
			}*/
		}
	}
}
