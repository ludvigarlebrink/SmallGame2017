#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
	: m_posX(0), m_posY(0)
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

	m_transform.SetPosition(m_posX, m_posY, 0.001f);

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
		m_posY += -1.1 * (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY));
		m_posX -= (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTX));
		//std::cout << "m_posY: " << m_posY << std::endl;
		std::cout << "m_posY: " << -1.1 * (m_input->GetAxisDirection(CONTROLLER_AXIS_LEFTY)) << std::endl;
	}
}

void LevelEditor::ButtonInput()
{
	if (m_input->GetButtonHeld(CONTROLLER_BUTTON_A))
	{
		m_level.AddBlock(m_posX, m_posY);
	}

	if (m_input->GetButtonHeld(CONTROLLER_BUTTON_X))
	{
		m_level.RemoveBlock(m_posX, m_posY);
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_B))
	{
		m_level.AddSpawnPoint(m_posX, m_posY);
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_Y))
	{
		exit(-1);
	}
}

void LevelEditor::ClampPos()
{
	if (m_posX >= SIZE_X)
	{
		m_posX = SIZE_X - 1;
	}
	else if (m_posX <= 1)
	{
		m_posX = 1;
	}

	if (m_posY >= SIZE_Y)
	{
		m_posY = SIZE_Y - 1;
	}
	else if (m_posY <= 1)
	{
		m_posY = 1;
	}
}

