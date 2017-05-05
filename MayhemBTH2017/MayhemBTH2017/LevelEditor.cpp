#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
{

	m_camera.SetPosition(glm::vec3(((SIZE_X / 2)), ((SIZE_Y / 2)), -51.2f));
	m_input = InputManager::Get();
	m_stateManager = StateManager::Get();
	m_videoManager = VideoManager::Get();
	m_timeManager = TimeManager::Get();

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

		m_levelMarker.Render(m_camera, m_levelGUI.GetCurrentUV());
		m_level.Render(m_camera);
		m_levelGUI.Render(m_camera);
		ButtonInput();
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
	if (m_input->GetAxis(CONTROLLER_AXIS_LEFT_Y) || m_input->GetAxis(CONTROLLER_AXIS_LEFT_X))
	{

		if (m_input->GetAxis(CONTROLLER_AXIS_LEFT_Y) > 0.3)
		{
			m_levelMarker.SetCurrentPosY(m_levelMarker.GetCurrentPosY() - 1);
		}
		else if (m_input->GetAxis(CONTROLLER_AXIS_LEFT_Y) < -0.3)
		{
			m_levelMarker.SetCurrentPosY(m_levelMarker.GetCurrentPosY() - (-1));
		}

		if (m_input->GetAxis(CONTROLLER_AXIS_LEFT_X) > 0.3)
		{
			m_levelMarker.SetCurrentPosX(m_levelMarker.GetCurrentPosX() - 1);
		}
		else if (m_input->GetAxis(CONTROLLER_AXIS_LEFT_X) < -0.3)
		{
			m_levelMarker.SetCurrentPosX(m_levelMarker.GetCurrentPosX() - (-1));
		}
	}

	//Right stick
	if (m_input->GetAxis(CONTROLLER_AXIS_RIGHT_Y) < -0.3 || m_input->GetAxis(CONTROLLER_AXIS_RIGHT_Y) > 0.3 || m_input->GetAxis(CONTROLLER_AXIS_RIGHT_X) < -0.3 || m_input->GetAxis(CONTROLLER_AXIS_RIGHT_X) > 0.3)
	{
		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x,
			m_camera.GetPosition().y - m_input->GetAxis(CONTROLLER_AXIS_RIGHT_Y) * m_timeManager->GetDeltaTime() * 600,
			m_camera.GetPosition().z));

		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x - m_input->GetAxis(CONTROLLER_AXIS_RIGHT_X) * m_timeManager->GetDeltaTime() * 600,
			m_camera.GetPosition().y,
			m_camera.GetPosition().z));
	}

	if (m_input->GetAxis(CONTROLLER_AXIS_TRIGGERRIGHT) != 0.0 && m_camera.GetPosition().z < -20.0)
	{
		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z + m_input->GetAxis(CONTROLLER_AXIS_TRIGGERRIGHT) * m_timeManager->GetDeltaTime() * 500));
	}

	else if (m_input->GetAxis(CONTROLLER_AXIS_TRIGGERLEFT) != 0.0 && m_camera.GetPosition().z > -70.0)
	{
		m_camera.SetPosition(glm::vec3(m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z - m_input->GetAxis(CONTROLLER_AXIS_TRIGGERLEFT) * m_timeManager->GetDeltaTime() * 500));
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

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_B))
	{
		glViewport(0, 0, 84, 48);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_level.Render(m_camera);
		m_videoManager->Swap();
		m_levelHandler.Export(m_level);
		m_levelHandler.ExportRegister();

		// FIX
		glViewport(0, 0, 1280, 720);
		// REMOVE

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

