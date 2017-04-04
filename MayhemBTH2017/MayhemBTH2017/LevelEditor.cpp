#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
	: m_posX(0), m_posY(0)
{
	m_camera.SetPosition(glm::vec3(8, 8, -24));
	m_input = InputManager::Get();
	m_green.Init("DebugGreen", false);

	Vertex verts[6];

	verts[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[0].normal = glm::vec3(0.5f, 0.5f, 0.0f);
	verts[0].texCoords = glm::vec2(0.0f, 1.0f);

	verts[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[1].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[1].texCoords = glm::vec2(0.0f, 1.0f);

	verts[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[2].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[2].texCoords = glm::vec2(0.0f, 1.0f);

	verts[3].position = glm::vec3(0.5f, -0.5f, 0.0f);
	verts[3].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[3].texCoords = glm::vec2(0.0f, 1.0f);

	verts[4].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	verts[4].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[4].texCoords = glm::vec2(0.0f, 1.0f);

	verts[5].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	verts[5].normal = glm::vec3(1.0f, 1.0f, 0.0f);
	verts[5].texCoords = glm::vec2(0.0f, 1.0f);

	m_transform.SetPosition(0, 0, 99);
	m_mesh.LoadMesh(verts, 6, 3);

}

LevelEditor::~LevelEditor()
{

}


//::.. UPDATE FUNCTIONS ..:://
void LevelEditor::Update()
{	
	
	Move();
	ClampPos();

	m_transform.SetPosition(m_posX, m_posY, 0.001f);

	m_green.Bind();
	m_green.Update(m_transform, m_camera);
	m_mesh.Render();

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_level.AddBlock(m_posX, m_posY);
	}

	m_level.Render(m_camera);
}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::Move()
{
	// MOVE THE POS;
	


	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		++m_posY;
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		--m_posY;
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	{
		++m_posX;
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		--m_posX;
	}
	
	// OSV
	//	--m_posX;
	//	++m_posY;
	//	--m_posY;

}

void LevelEditor::ClampPos()
{
	if (m_posX >= SIZE_X)
	{
		m_posX = SIZE_X - 1;
	}
	else if (m_posX < 0)
	{
		m_posX = 0;
	}

	if (m_posY >= SIZE_Y)
	{
		m_posY = SIZE_Y - 1;
	}
	else if (m_posY < 0)
	{
		m_posY = 0;
	}
}

