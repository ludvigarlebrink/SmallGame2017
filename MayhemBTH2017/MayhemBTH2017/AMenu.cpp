#include "AMenu.h"

#include <iostream>

AMenu::AMenu()
	: m_isActive(false)
{
	// Do nothing...
	m_stateManager = StateManager::Get();
	m_currentSelection = 0;
	m_shader.Init("DebugGreen", false);
}


AMenu::~AMenu()
{
	// Do nothing...
}


void AMenu::Render()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->Render();
	}

	// FIX THIS :D
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Camera camera;

	m_shader.Bind();
	camera.SetPosition(glm::vec3(0.0f, 0.0f, -11.0f));
	m_transform.SetScale(5.0f, 5.0f, 1.0f);
	m_shader.Update(m_transform, camera);

	for (uint32_t i = 0; i < m_button.size(); i++)
	{
		m_transform.SetPosition(glm::vec3(0.0f, -(1.0f * i), -0.1f * i));
		m_shader.Update(m_transform, camera);
		
		if (m_button[i]->isActive)
		{
			m_shader.TempUpdateAlpha(1.0f);
			m_button[i]->texture->Bind();
			m_button[i]->text->Render();
		}
		else
		{
			m_shader.TempUpdateAlpha(0.4f);
			m_button[i]->texture->Bind();
			m_button[i]->text->Render();
		}
	}

	m_shader.TempUpdateAlpha(1.0f);
}

void AMenu::GoForward()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->GoForward();
		return;
	}

	if (m_type[m_currentSelection] == SUBMENU)
	{
		m_subMenu[m_index[m_currentSelection]]->SetIsActive(true);
		m_isActive = false;

	}
	else if (m_type[m_currentSelection] == GAMESTATE)
	{
		m_stateManager->SetCurrentState(m_gameState[m_index[m_currentSelection]]);
		FreeChildren();
	}
}

void AMenu::GoBack()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->GoBack();
		return;
	}

	if (m_parent == nullptr)
	{
		return;
	}

	m_parent->SetIsActive(true);
	m_isActive = false;
}

//::.. MODIFY FUNCTIONS ..:://
void AMenu::MoveUp()
{

	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->MoveUp();
		return;
	}

	m_button[m_currentSelection]->isActive = false;

	--m_currentSelection;

	if (m_currentSelection < 0)
	{
		m_currentSelection = 0;
	}

	m_button[m_currentSelection]->isActive = true;
}

void AMenu::MoveDown()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->MoveDown();
		return;
	}

	// TEMP
	m_button[m_currentSelection]->isActive = false;

	++m_currentSelection;

	if (m_currentSelection >= m_index.size())
	{
		m_currentSelection = m_index.size() - 1;
	}

	m_button[m_currentSelection]->isActive = true;
}


//::.. GET FUNCTIONS ..:://
AMenu * AMenu::GetParent()
{
	return m_parent;
}

bool AMenu::GetIsActive()
{
	return m_isActive;
}

//::.. SET FUNCTIONS ..:://
void AMenu::SetParent(AMenu * parent)
{
	m_parent = parent;
}

void AMenu::SetIsActive(bool value)
{
	m_isActive = value;
}


//::.. PROTECTED FUNCTIONS ..:://
void AMenu::AddChild(AMenu *subMenu, char* title)
{
	m_subMenu.push_back(subMenu);
	m_index.push_back(m_subMenu.size() - 1);
	m_type.push_back(SUBMENU);

	Button * button = new Button;
	Text * text = new Text;
	text->Init();
	button->text = text;
	if (m_button.size() == 0)
	{
		button->isActive = true;
	}
	else
	{
		button->isActive = false;
	}
	m_button.push_back(button);
}

void AMenu::AddChild(GameState gameState, char* title)
{
	m_gameState.push_back(gameState);
	m_index.push_back(m_gameState.size() - 1);
	m_type.push_back(GAMESTATE);
	
	TextureImporter textImp;
	std::string tmp = ".\\Assets\\Sprites\\";
	tmp.append(title);
	tmp.append(".png");
	Texture * texture = new Texture;
	*texture = textImp.Import(tmp.c_str());;

	Button * button = new Button;
	Text * text = new Text;
	text->Init();
	button->texture = texture;
	button->text = text;

	if (m_button.size() == 0)
	{
		button->isActive = true;
	}
	else
	{
		button->isActive = false;
	}

	m_button.push_back(button);
}

AMenu * AMenu::GetChildAt(uint32_t index)
{
	return m_subMenu[index];
}

void AMenu::FreeChildren()
{
	if (m_parent == nullptr)
	{
		m_isActive = true;
		return;
	}

	m_isActive = false;
	m_parent->FreeChildren();
}

