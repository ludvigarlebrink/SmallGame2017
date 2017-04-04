#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
{
	m_input = InputManager::Get();
}

LevelEditor::~LevelEditor()
{

}


//::.. UPDATE FUNCTIONS ..:://
void LevelEditor::Update()
{
	// DO A LOT OF SHIT
	
	
	Move();

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

