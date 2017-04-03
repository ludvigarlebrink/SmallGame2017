#include "GUI.h"



GUI::GUI(const std::string & filename, bool geom) 
	: AShader(filename, geom)
{

}


GUI::~GUI()
{
}

void GUI::AddSprite(Sprite sprite)
{
	m_spriteArr.PushBack(sprite);
}

void GUI::Update()
{

	int mouse_x;
	int mouse_y;

	SDL_GetMouseState(&mouse_x, &mouse_y);

	float new_mouseX = 600 / (float)mouse_x;
	float new_mouseY = 400 / (float)mouse_y;

	for (int i = 0; i < m_spriteArr.GetSize(); i++)
	{
		m_spriteArr[i].Update(mouse_x, mouse_y);
	}
}

void GUI::Render()
{
	Bind();
	m_spriteArr[0].Draw();
	Release();
}

void GUI::AddAttributeLocation()
{

}
