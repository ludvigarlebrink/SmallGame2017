#include "LevelEditorGUI.h"



LevelEditorGUI::LevelEditorGUI()
{
	//	m_width = 1280;
	//	m_height = 720;

	m_input = InputManager::Get();

	// Closed menu init
	m_closedMenu.SetTexture(".\\Assets\\Sprites\\ClosedMenu1.png");
	m_closedMenu.SetSize(m_closedMenu.GetSizeX() / 3, m_closedMenu.GetSizeY() / 2);
	m_closedMenu.SetPosition(-530, 320);

	// Block menu init
	m_blockMenu.SetTexture(".\\Assets\\Sprites\\MainMenu.png");
	m_blockMenu.SetSize(m_closedMenu.GetSizeX(), 650);
	m_blockMenu.SetPosition(m_closedMenu.GetPosX(), m_closedMenu.GetPosY() - 315);

	m_menuClosed = true;
	m_nSize = 80;
	m_hSize = 120;
	m_pos = 0;

	m_blockArray[0].SetTexture(".\\Assets\\Sprites\\BlueButton.png");
	m_blockArray[1].SetTexture(".\\Assets\\Sprites\\GreenButton.png");
	m_blockArray[2].SetTexture(".\\Assets\\Sprites\\YellowButton.png");
	m_blockArray[3].SetTexture(".\\Assets\\Sprites\\CrossHairButton.png");
	
	m_blockArray[0].SetPosition(-50, 50);
	m_blockArray[1].SetPosition(50, 50);
	m_blockArray[2].SetPosition(-50, -50);
	m_blockArray[3].SetPosition(50, -50);

	for (int i = 0; i < NUM_SELECTIONS; i++)
	{
		m_blockArray[i].SetSize(80, 80);
	}

	m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
}


LevelEditorGUI::~LevelEditorGUI()
{
	// Do nothing...
}

bool LevelEditorGUI::GetMenuClosed()
{
	return m_menuClosed;
}

void LevelEditorGUI::SetMenuClosed(bool value)
{
	m_menuClosed = value;
}

void LevelEditorGUI::Render()
{
	if (m_menuClosed == true)
	{
		m_closedMenu.Render();
	}
	else
	{
		Input();
		for (int i = 0; i < NUM_SELECTIONS; i++)
		{
			m_blockArray[i].Render();
		}
		m_blockMenu.Render();

	}
}

void LevelEditorGUI::Input()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_pos - 1 >= 0 )
		{
			m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
			m_pos -= 2;
			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		if (m_pos + 1 < NUM_SELECTIONS)
		{
			m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
			m_pos += 2;
			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	{
		if (m_pos - 1 >= 0)
		{
			m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
			--m_pos;
			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		if (m_pos + 1 < NUM_SELECTIONS)
		{
			m_blockArray[m_pos].SetSize(m_nSize, m_nSize);
			++m_pos;
			m_blockArray[m_pos].SetSize(m_hSize, m_hSize);
		}
	}
}
