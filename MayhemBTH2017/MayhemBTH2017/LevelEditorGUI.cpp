#include "LevelEditorGUI.h"



LevelEditorGUI::LevelEditorGUI()
{
	//	m_width = 1280;
	//	m_height = 720;

	m_input = InputManager::Get();

	m_text.SetText("BLOCKS");
	m_text.SetSize(80);
	m_text.SetPosition(-530, 320);
	m_text.SetFont(".\\Assets\\Fonts\\steelfish.ttf");
	m_text.SetPivot(UIText::LEFT);
	m_text.SetColor(255, 255, 255, 255);

	// Block menu
	m_texFile.open(".\\Assets\\Sprites\\blockMenu.txt");
	m_index = 0;
	while (std::getline(m_texFile, m_line))
	{
		m_blockArray[m_index].SetTexture(m_line.c_str());
		m_index++;
	}
	m_texFile.close();

	// Prop menu
	m_texFile.open(".\\Assets\\Sprites\\propMenu.txt");
	m_index = 0;
	while (std::getline(m_texFile, m_line))
	{
		m_propArray[m_index].SetTexture(m_line.c_str());
		m_index++;
	}
	m_texFile.close();

	// Closed menu init
	m_closedMenu.SetTexture(".\\Assets\\Sprites\\ClosedMenu1.png");
	m_closedMenu.SetSize(m_closedMenu.GetSizeX() / 3, m_closedMenu.GetSizeY() / 2);
	m_closedMenu.SetPosition(-530, 320);

	// Block menu init
	m_blockMenu.SetTexture(".\\Assets\\Sprites\\MainMenu.png");
	m_blockMenu.SetSize(m_closedMenu.GetSizeX(), 650);
	m_blockMenu.SetPosition(m_closedMenu.GetPosX(), m_closedMenu.GetPosY() - 315);

	m_nSize = 50;
	m_hSize = 70;
	m_pos = 0;

	m_blockArray[0].SetPosition(-575, 175);
	m_blockArray[1].SetPosition(-500, 175);
	m_blockArray[2].SetPosition(-575, 100);
	m_blockArray[3].SetPosition(-500, 100);

	m_propArray[0].SetPosition(-575, 175);
	m_propArray[1].SetPosition(-500, 175);
	m_propArray[2].SetPosition(-575, 100);
	m_propArray[3].SetPosition(-500, 100);

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		m_blockArray[i].SetSize(m_nSize, m_nSize);
	}

	for (int i = 0; i < NUM_PROPS; i++)
	{
		m_propArray[i].SetSize(m_nSize, m_nSize);
	}

	m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
	m_propArray[m_pos].SetSize(m_hSize, m_hSize);
	m_state = CLOSED_MENU;
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
	case CLOSED_MENU:
		m_closedMenu.Render();
		break;

	case BLOCK_MENU:
		Input();
		m_blockMenu.Render();
		m_text.Render();
		RenderArray(m_blockArray, NUM_BLOCKS);
		break;

	case PROP_MENU:
		Input();
		m_blockMenu.Render();
		RenderArray(m_propArray, NUM_PROPS);
		break;

	case BACKGROUND_MENU:
		Input();
		m_blockMenu.Render();
		break;
	}

}

void LevelEditorGUI::RenderArray(UIImage menu_array[], int num_array)
{
	for (int i = 0; i < num_array; i++)
	{
		menu_array[i].Render();
	}
}


void LevelEditorGUI::Input()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		switch (m_state)
		{
		case BLOCK_MENU:
			if (m_pos - 2 >= 0)
			{
				m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
				m_pos -= 2;
				m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;

		case PROP_MENU:
			if (m_pos - 2 >= 0)
			{
				m_propArray[m_pos].SetSize(m_nSize, m_nSize);
				m_pos -= 2;
				m_propArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;
		}

	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{

		switch (m_state)
		{
		case BLOCK_MENU:
			if (m_pos + 2 < NUM_BLOCKS)
			{
				m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
				m_pos += 2;
				m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;

		case PROP_MENU:
			if (m_pos + 2 < NUM_PROPS)
			{
				m_propArray[m_pos].SetSize(m_nSize, m_nSize);
				m_pos += 2;
				m_propArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;
		}

	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	{

		switch (m_state)
		{
		case BLOCK_MENU:
			if (m_pos - 1 >= 0)
			{
				m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
				--m_pos;
				m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;

		case PROP_MENU:
			if (m_pos - 1 >= 0)
			{
				m_propArray[m_pos].SetSize(m_nSize, m_nSize);
				--m_pos;
				m_propArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		switch (m_state)
		{
		case BLOCK_MENU:
			if (m_pos + 1 < NUM_BLOCKS)
			{
				m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
				++m_pos;
				m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;

		case PROP_MENU:
			if (m_pos + 1 < NUM_PROPS)
			{
				m_propArray[m_pos].SetSize(m_nSize, m_nSize);
				++m_pos;
				m_propArray[m_pos].SetSize(m_hSize, m_hSize);
			}
			break;
		}
	}

	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_RB))
	{
		if (m_state + 1 <= 3)
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
		if (m_state - 1 != CLOSED_MENU)
		{
			m_state--;

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
}
