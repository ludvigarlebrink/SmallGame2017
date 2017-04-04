#include "LevelEditor.h"


//::.. CONSTRUCTORS ..:://
LevelEditor::LevelEditor()
{

}

LevelEditor::~LevelEditor()
{

}


//::.. UPDATE FUNCTIONS ..:://
void LevelEditor::Update()
{
	// DO A LOT OF SHIT
	Move();

	if (m_input->GetButtonDown(0,0))
		std::cout << "Hejsan!" << std::endl;
	
		m_level.Render();

}


//::.. HELP FUNCTIONS ..:://
void LevelEditor::Move()
{
	// MOVE THE POS;

	++m_posX;
	--m_posX;
	++m_posY;
	--m_posY;

}

