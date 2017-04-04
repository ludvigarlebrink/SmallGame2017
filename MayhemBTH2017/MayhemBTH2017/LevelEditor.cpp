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

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_Y))
	{
		m_level.SetOccupied(m_posX, m_posY, !m_level.GetOccupied(m_posX, m_posY));
	}


	m_level.Render();
}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::Move()
{
	// MOVE THE POS;
	
	// IF RIGHT IS PRESSED
	++m_posX;
	
	// OSV
	--m_posX;
	++m_posY;
	--m_posY;

}

