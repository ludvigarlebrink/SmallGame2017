#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
	: m_currentPosX(0), m_currentPosY(0)
{
	m_camera.SetRotation(0.0f, -10.0f);
	m_camera.SetPosition(glm::vec3((SIZE_X / 2) - 0.5f, (SIZE_Y / 2) + 10, -70));
	m_input = InputManager::Get();
	m_green.Init("DebugGreen", false);

	Vertex verts[6];

	verts[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[0].normal = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[0].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[1].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[1].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[2].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[2].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[3].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[3].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[3].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[4].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[4].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[4].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	verts[5].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	verts[5].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[5].texCoordsAlpha = glm::vec3(0.0f, 1.0f, 1.0f);

	m_transform.SetPosition(0.0f, 0.0f, 0.0f);
	m_mesh.LoadMesh(verts, 6);

}

LevelEditor::~LevelEditor()
{

}


//::.. UPDATE FUNCTIONS ..:://
void LevelEditor::Update()
{
	AxisMove();
	ClampPos();
	ButtonInput();

	m_transform.SetPosition(m_currentPosX, m_currentPosY, 0.001f);

	m_green.Bind();
	m_green.Update(m_transform, m_camera);
	m_mesh.Render();

	m_level.Render(m_camera);
}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::AxisMove()
{
	//Left stick

	// Up/Down
	if (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY) != 0.0f || m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX) != 0.0f)
	{
		m_currentPosY += -1.1 * (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY));
		m_currentPosX -= (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX));
		//std::cout << "m_currentPosY: " << m_currentPosY << std::endl;
		std::cout << "m_currentPosY: " << -1.1 * (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY)) << std::endl;
	}
}

void LevelEditor::ButtonInput()
{
	if (m_input->GetButtonHeld(CONTROLLER_BUTTON_A))
	{
		m_level.AddBlock(m_currentPosX, m_currentPosY);
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

