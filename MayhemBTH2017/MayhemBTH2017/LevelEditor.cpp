#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
{

	m_camera.SetPosition(glm::vec3(((SIZE_X / 2)), ((SIZE_Y / 2)), -51.2f));
	m_input = InputManager::Get();
	m_stateManager = StateManager::Get();
	m_levelHandler.Init();

	m_timer.SetTimer(0.1f, true, true);
}

LevelEditor::~LevelEditor()
{

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

		ButtonInput();
		m_levelMarker.Update(m_camera);
		m_level.Render(m_camera);
		m_levelGUI.Render();
		break;
	case MENU:
		break;
	case SAVE:
		
		ButtonInput();
		m_level.Render(m_camera);
		
		break;
	default:
		break;
	}
}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::AxisMove()
{
	//Left stick
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY) || m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX))
	{

		if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY) > 0.3)
		{
			m_levelMarker.SetCurrentPosY(m_levelMarker.GetCurrentPosY() - 1);
		}
		else if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY) < -0.3)
		{
			m_levelMarker.SetCurrentPosY(m_levelMarker.GetCurrentPosY() - (-1));
		}

		if(m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX) > 0.3)
		{
			m_levelMarker.SetCurrentPosX(m_levelMarker.GetCurrentPosX() - 1);
		}
		else if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX) < -0.3)
		{
			m_levelMarker.SetCurrentPosX(m_levelMarker.GetCurrentPosX() - (-1));
		}
	}

	//Right stick
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f)
	{
		// Do nothing...
	}
}

void LevelEditor::ButtonInput()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		m_u.x++;
	}

	//Left stick
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		m_u.x = 0;
	}
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
				m_level.AddBlock(x, y, m_u);
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

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_B))
	{
		std::cout << "Pressed B: " << std::endl;
		m_levelHandler.Export(m_level);
		m_levelHandler.ExportRegister();
		// REMOVE
		temp.SaveImage(".\\Assets\\Textures\\TextureTestE.TGA");

	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_Y))
	{
		Reset();
		uint32_t p = 1;
		m_levelHandler.Import(m_level, p);
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		if (m_state == SAVE)
		{
			m_state = EDIT;
		}
		else
		{
			
			m_state = SAVE;
		}
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

