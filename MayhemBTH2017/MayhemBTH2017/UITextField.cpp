#include "UITextField.h"



UITextField::UITextField()
{
	m_text.SetText("");
	
	m_background.SetColor(0, 0, 0, 50);
	m_background.SetSize(568, 52);
	
	m_field.SetColor(220, 220, 220);
	m_field.SetSize(560, 44);

	m_posX = 0;
	m_posY = 60;

	m_text.SetPivot(UIText::LEFT);
	m_text.SetPosition(0.0f, m_posY);
	m_text.SetColor(235, 235, 180, 255);
	m_text.SetFont(".\\Assets\\Fonts\\Snap.ttf");
	m_background.SetPosition(m_posX, m_posY);
	m_field.SetPosition(m_posX, m_posY);
}


UITextField::~UITextField()
{
}


void UITextField::Render()
{
	m_background.Render();
	m_field.Render();
	m_text.Render();
}


//::.. SET FUNCTIONS ..:://
void UITextField::SetText(const char * text)
{
	m_text.SetText(text);
}
