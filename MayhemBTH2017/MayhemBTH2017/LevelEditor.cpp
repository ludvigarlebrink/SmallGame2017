#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
{

	m_input = InputManager::Get();
	m_stateManager = StateManager::Get();
	m_videoManager = VideoManager::Get();
	m_timeManager = TimeManager::Get();

	m_camera.SetPosition(glm::vec3(((SIZE_X / 2)), ((SIZE_Y / 2)), -51.2f));
	m_timer.SetTimer(0.1f, true, true);

	// THE BACKGROUND
	m_fill.SetSize(m_videoManager->GetWidth(), m_videoManager->GetHeight());
	m_fill.SetColor(0, 0, 0, 170);

	// Text
	m_menuText[0].SetText("SAVE LEVEL");
	m_menuText[0].SetSize(80);
	m_menuText[0].SetPosition(0, 145);
	m_menuText[0].SetFont(".\\Assets\\Fonts\\steelfish.ttf");
	m_menuText[0].SetPivot(UIText::CENTER);
	m_menuText[0].SetColor(255, 255, 255, 255);

	m_menuText[1].SetText("LOAD LEVEL");
	m_menuText[1].SetSize(80);
	m_menuText[1].SetPosition(0, 0);
	m_menuText[1].SetFont(".\\Assets\\Fonts\\steelfish.ttf");
	m_menuText[1].SetPivot(UIText::CENTER);
	m_menuText[1].SetColor(255, 255, 255, 255);

	m_menuText[2].SetText("EXIT");
	m_menuText[2].SetSize(80);
	m_menuText[2].SetPosition(0, -145);
	m_menuText[2].SetFont(".\\Assets\\Fonts\\steelfish.ttf");
	m_menuText[2].SetPivot(UIText::CENTER);
	m_menuText[2].SetColor(255, 255, 255, 255);

	m_textPos = 0;
	m_menuText[m_textPos].SetSize(100);
	m_menuText[m_textPos].SetColor(255, 0, 0, 128);
}

LevelEditor::~LevelEditor()
{
	// Do nothing...
}


//::.. UPDATE FUNCTIONS ..:://
void LevelEditor::Update()
{

	switch (m_state)
	{
	case EDIT:
		if (m_timer.Update())
		{
			AxisMove();
		}


		m_levelMarker.Render(m_camera, m_levelGUI.GetCurrentUV());
		m_level.Render(m_camera);
		m_levelGUI.Render(m_camera);

		ButtonInput();
		break;
	case MENU:
		// Background
		m_fill.Render();

		// Text
		m_menuText[0].Render();
		m_menuText[1].Render();
		m_menuText[2].Render();


		MenuInput();
		break;

	case SAVE:
		m_virtualKeyboard.Render();
		MenuInput();
		break;

	case LOAD:
		Reset();
		m_levelID++;
		m_levelHandler.Import(m_level, m_levelID);
		m_state = EDIT;
		break;
	default:
		break;
	}
}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::AxisMove()
{
	//Left stick
	if (m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_Y) || m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_X))
	{

		if (m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_Y) > 0.3)
		{
			m_levelMarker.SetCurrentPosY(m_levelMarker.GetCurrentPosY() - 1);
		}
		else if (m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_Y) < -0.3)
		{
			m_levelMarker.SetCurrentPosY(m_levelMarker.GetCurrentPosY() - (-1));
		}

		if (m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_X) > 0.3)
		{
			m_levelMarker.SetCurrentPosX(m_levelMarker.GetCurrentPosX() - 1);
		}
		else if (m_input->GetAxisRaw(CONTROLLER_AXIS_LEFT_X) < -0.3)
		{
			m_levelMarker.SetCurrentPosX(m_levelMarker.GetCurrentPosX() - (-1));
		}
	}

	//Right stick
	if (m_input->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y) < -0.3 || m_input->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y) > 0.3 || m_input->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X) < -0.3 || m_input->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X) > 0.3)
	{
		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x,
			m_camera.GetPosition().y - m_input->GetAxisRaw(CONTROLLER_AXIS_RIGHT_Y) * m_timeManager->GetDeltaTime() * 600,
			m_camera.GetPosition().z));

		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x - m_input->GetAxisRaw(CONTROLLER_AXIS_RIGHT_X) * m_timeManager->GetDeltaTime() * 600,
			m_camera.GetPosition().y,
			m_camera.GetPosition().z));
	}

	if (m_input->GetAxisRaw(CONTROLLER_AXIS_TRIGGERRIGHT) > 0.1 && m_camera.GetPosition().z < -20.0)
	{
		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z + m_input->GetAxisRaw(CONTROLLER_AXIS_TRIGGERRIGHT) * m_timeManager->GetDeltaTime() * 500));
	}

	else if (m_input->GetAxisRaw(CONTROLLER_AXIS_TRIGGERLEFT) > 0.1 && m_camera.GetPosition().z > -70.0)
	{
		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z - m_input->GetAxisRaw(CONTROLLER_AXIS_TRIGGERLEFT) * m_timeManager->GetDeltaTime() * 500));
	}
}

void LevelEditor::ButtonInput()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_levelMarker.SetSavedPosX(m_levelMarker.GetCurrentPosX());
		m_levelMarker.SetSavedPosY(m_levelMarker.GetCurrentPosY());
		m_levelMarker.SetMarkerMode(ADD_BLOCK);
	}

	if (m_input->GetButtonUp(CONTROLLER_BUTTON_A) && m_levelMarker.GetMarkerMode())
	{
		m_levelMarker.SetMarkerMode(NORMAL);

		for (size_t x = m_levelMarker.GetStartX(); x <= m_levelMarker.GetEndX(); x++)
		{
			for (size_t y = m_levelMarker.GetStartY(); y <= m_levelMarker.GetEndY(); y++)
			{
				m_level.AddBlock(x, y, m_levelGUI.GetCurrentUV());
			}
		}
	}

	if (m_input->GetButtonUp(CONTROLLER_BUTTON_X) && m_levelMarker.GetMarkerMode())
	{
		m_levelMarker.SetMarkerMode(NORMAL);

		for (size_t x = m_levelMarker.GetStartX(); x <= m_levelMarker.GetEndX(); x++)
		{
			for (size_t y = m_levelMarker.GetStartY(); y <= m_levelMarker.GetEndY(); y++)
			{
				m_level.RemoveBlock(x, y);
			}
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_X))
	{
		m_levelMarker.SetSavedPosX(m_levelMarker.GetCurrentPosX());
		m_levelMarker.SetSavedPosY(m_levelMarker.GetCurrentPosY());
		m_levelMarker.SetMarkerMode(REMOVE_BLOCK);
	}

	if (m_input->GetButtonUp(CONTROLLER_BUTTON_X))
	{
		m_levelMarker.SetMarkerMode(NORMAL);
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		m_state = MENU;
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_BACK))
	{
		if (m_state != SAVE)
		{
			if (m_levelGUI.GetState() == GUI_CLOSED)
			{
				m_levelGUI.SetState(GUI_BLOCK);
			}
			else
			{
				m_levelGUI.SetState(GUI_CLOSED);
			}
		}
	}
}

void LevelEditor::MenuInput()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_textPos - 1 >= 0)
		{
			m_menuText[m_textPos].SetColor(255, 255, 255, 255);
			m_menuText[m_textPos].SetSize(90);
			m_textPos--;
			m_menuText[m_textPos].SetSize(100);
			m_menuText[m_textPos].SetColor(255, 0, 0, 128);
		}
	}

	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		if (m_textPos + 1 < 3)
		{
			m_menuText[m_textPos].SetColor(255, 255, 255, 255);
			m_menuText[m_textPos].SetSize(90);
			m_textPos++;
			m_menuText[m_textPos].SetSize(100);
			m_menuText[m_textPos].SetColor(255, 0, 0, 128);
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		if (m_state == MENU)
			m_state = EDIT;
		else if (m_state == SAVE)
		{
			// Add confirmation for save
			m_level.SetName(m_virtualKeyboard.GetString());
			glViewport(0, 0, 84, 48);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_level.Render(m_camera);
			m_videoManager->Swap();
			m_levelHandler.Export(m_level, m_levelGUI.GetPropPlacer());
			m_levelHandler.ExportRegister();
			// FIX
			glViewport(0, 0, 1280, 720);
			// REMOVE
			m_textPos = 0;
			m_state = MENU;
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A) && m_state == MENU)
	{
		switch (m_textPos)
		{
		case 0:
			m_state = SAVE;
			break;

		case 1:
			m_state = LOAD;
			break;

		case 2:
			// Exit
			break;
		}
	}
}

void LevelEditor::Reset()
{
	for (size_t x = 1; x < SIZE_X; x++)
	{
		for (size_t y = 1; y < SIZE_Y; y++)
		{
			if (m_level.GetIsOccupied(x, y))
				m_level.RemoveBlock(x, y);
		}
	}
}

