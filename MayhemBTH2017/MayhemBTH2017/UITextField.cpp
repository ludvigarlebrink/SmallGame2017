#include "UITextField.h"



UITextField::UITextField()
{
	m_text.SetText("HEJ JAG AR 40 AR");
	
	m_background.SetColor(0, 0, 0, 50);
	m_background.SetSize(568, 48);
	
	m_field.SetColor(172, 172, 172);
	m_field.SetSize(560, 40);

	m_posX = 0;
	m_posY = 60;

	m_text.SetPositon(m_posX, m_posY);
	m_background.SetPositon(m_posX, m_posY);
	m_field.SetPositon(m_posX, m_posY);
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
