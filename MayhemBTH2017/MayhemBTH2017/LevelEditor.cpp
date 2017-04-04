#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
	: m_posX(0), m_posY(0)
{
	m_input = InputManager::Get();
}

LevelEditor::~LevelEditor()
{

}


//::.. UPDATE FUNCTIONS ..:://
void LevelEditor::Update()
{	
	
	Move();
	ClampPos();

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_level.AddBlock(m_posX, m_posY);
	}

	m_level.Render();
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

