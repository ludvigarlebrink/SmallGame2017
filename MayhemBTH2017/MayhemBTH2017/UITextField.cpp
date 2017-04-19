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
	m_text.SetPositon(m_posX - (560 / 2) + 4, m_posY);
	m_text.SetColor(255, 255, 255);
	m_text.SetFont(".\\Assets\\Fonts\\steelfish.ttf");
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


void UITextField::SetPos(int32_t x, int32_t y)
{

}
