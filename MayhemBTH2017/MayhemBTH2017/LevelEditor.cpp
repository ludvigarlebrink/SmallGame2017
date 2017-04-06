#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
	: m_currentPosX(0), m_currentPosY(0)
{
	m_camera.SetRotation(0.0f, -0.0f);
	m_camera.SetPosition(glm::vec3(((SIZE_X / 2) - 0.5f), ((SIZE_Y / 2) + 0.5f), -60));
	m_input = InputManager::Get();
	m_green.Init("DebugGreen", false);

	m_texture = texImp.Import(".\\Assets\\Textures\\stone.jpg");

	Vertex verts[6];

	float scaler = 1.0f;

	m_timer.SetTimer(0.1f, true, true);

	verts[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[0].normal = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[0].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 1.0f);

	verts[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[1].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[1].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 1.0f);

	verts[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[2].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[3].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[3].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[4].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[4].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[4].texCoordsAlpha = glm::vec3(1.0f, 0.0f, 1.0f);

	verts[5].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	verts[5].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[5].texCoordsAlpha = glm::vec3(1.0f, 1.0f, 1.0f);

	m_transform.SetPosition(0.0f, 0.0f, 0.0f);
	m_mesh.LoadMesh(verts, 6);

}

LevelEditor::~LevelEditor()
{

}


//::.. UPDATE FUNCTIONS ..:://
void LevelEditor::Update()
{	
	if (m_timer.Update())
	{
		AxisMove();
	}
	ClampPos();
	ButtonInput();
	m_texture.Bind();
	RenderSelector();
	
	m_level.Render(m_camera);
}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::AxisMove()
{
	//Left stick
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f)
	{
		m_currentPosY -= m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY);
		m_currentPosX -= m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX);
	}

	//Right stick
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTX) != 0.0f)
	{
		m_currentPosY -= m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTY);
		m_currentPosX -= m_input->GetAxisDirection(CONTROLLER_AXIS_RIGHTX);
	}
}

void LevelEditor::ButtonInput()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_savedPosX = m_currentPosX;
		m_savedPosY = m_currentPosY;
	}

	if (m_input->GetButtonUp(CONTROLLER_BUTTON_A))
	{

		uint32_t startX;
		uint32_t startY;
		uint32_t endX;
		uint32_t endY;
		
		if (m_currentPosX > m_savedPosX)
		{
			startX = m_savedPosX;
			endX = m_currentPosX;
		}
		else
		{
			startX = m_currentPosX;
			endX = m_savedPosX;
		}
		
		if (m_currentPosY > m_savedPosY)
		{
			startY = m_savedPosY;
			endY = m_currentPosY;
		}
		else
		{
			startY = m_currentPosY;
			endY = m_savedPosY;
		}

		for (size_t x = startX; x <= endX; x++)
		{
			for (size_t y = startY; y <= endY; y++)
			{
				m_level.AddBlock(x, y);
			}
		}
	}

	if (m_input->GetButtonHeld(CONTROLLER_BUTTON_X))
	{
		m_level.RemoveBlock(m_currentPosX, m_currentPosY);
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_B))
	{
		m_level.AddSpawnPoint(m_currentPosX, m_currentPosY);
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_Y))
	{
		exit(-1);
	}
}

void LevelEditor::ClampPos()
{
	if (m_currentPosX >= SIZE_X)
	{
		m_currentPosX = SIZE_X - 1;
	}
	else if (m_currentPosX <= 1)
	{
		m_currentPosX = 1;
	}

	if (m_currentPosY >= SIZE_Y)
	{
		m_currentPosY = SIZE_Y - 1;
	}
	else if (m_currentPosY <= 1)
	{
		m_currentPosY = 1;
	}
}

void LevelEditor::RenderSelector()
{
	m_green.Bind();

	Transform tran;
	

	if (m_input->GetButtonHeld(CONTROLLER_BUTTON_A))
	{
		uint32_t startX;
		uint32_t startY;
		uint32_t endX;
		uint32_t endY;

		if (m_currentPosX > m_savedPosX)
		{
			startX = m_savedPosX;
			endX = m_currentPosX;
		}
		else
		{
			startX = m_currentPosX;
			endX = m_savedPosX;
		}

		if (m_currentPosY > m_savedPosY)
		{
			startY = m_savedPosY;
			endY = m_currentPosY;
		}
		else
		{
			startY = m_currentPosY;
			endY = m_savedPosY;
		}

		for (size_t x = startX; x <= endX; x++)
		{
			for (size_t y = startY; y <= endY; y++)
			{
				tran.SetPosition(x, y, -2.001f);
				m_green.Update(tran, m_camera);
				m_mesh.Render();
			}
		}
	}
	else
	{
		m_transform.SetPosition(m_currentPosX, m_currentPosY, -2.001f);
		m_green.Update(m_transform, m_camera);
		m_mesh.Render();
	}

}

