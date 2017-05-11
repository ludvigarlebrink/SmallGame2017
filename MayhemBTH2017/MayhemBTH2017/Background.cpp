#include "Background.h"



Background::Background()
{
	m_backgroundType = 0;
	InitBackground();
}


Background::~Background()
{
}


void Background::UpdateAndRender()
{
	switch (m_backgroundType)
	{
	case GRAND_CANYON:
		UpdateGrandCanyon();
		break;
	case PIRATE:
		break;
	case PARTY:
		break;
	default:
		break;
	}
}


void Background::SetBackground(uint32_t backgroundType)
{
	m_backgroundType = backgroundType;
	InitBackground();
}


//::.. HELP FUNCTIONS ..:://
void Background::UpdateGrandCanyon()
{
	float deltaHeight = VideoManager::Get()->GetHeight() / 1080.0f;
	float deltaWidth = VideoManager::Get()->GetWidth() / 1920.0f;

	m_sprites[1].SetPosition((m_sprites[1].GetPosX() - (TimeManager::GetDeltaTime() * 10.0f)), 300 * deltaHeight);
//	if (m_sprites[1].GetPosX() < -1300.0f * deltaWidth)
//	{
//		m_sprites[1].SetPosition(1300.0f * deltaWidth, 300 * deltaHeight);
//	}

	std::cout << m_sprites[1].GetPosX() << std::endl;
	for (uint32_t i = 0; i < 7; i++)
	{
		m_sprites[i].Render();
	}
}


void Background::UpdatePirate()
{
}


void Background::UpdateParty()
{
}


void Background::InitBackground()
{
	float deltaHeight = VideoManager::Get()->GetHeight() / 1080.0f;
	float deltaWidth = VideoManager::Get()->GetWidth() / 1920.0f;

	switch (m_backgroundType)
	{
	case GRAND_CANYON:
		m_sprites.resize(7);

		m_sprites[0].SetTexture(".\\Assets\\Sprites\\GCBack.png");
		m_sprites[0].SetSize(VideoManager::Get()->GetWidth(), VideoManager::Get()->GetHeight());

		m_sprites[1].SetTexture(".\\Assets\\Sprites\\GCCloud5.png");
		m_sprites[1].SetSize(234 * deltaWidth, 96 * deltaHeight);
		m_sprites[1].SetPosition(80 * deltaWidth, -400 * deltaHeight);

		m_sprites[2].SetTexture(".\\Assets\\Sprites\\GCCloud2.png");
		m_sprites[2].SetSize(272 * deltaWidth, 116 * deltaHeight);
		m_sprites[2].SetPosition(80 * deltaWidth, -300 * deltaHeight);

		m_sprites[3].SetTexture(".\\Assets\\Sprites\\GCCloud3.png");
		m_sprites[3].SetSize(175 * deltaWidth, 65 * deltaHeight);
		m_sprites[3].SetPosition(80 * deltaWidth, -400 * deltaHeight);

		m_sprites[4].SetTexture(".\\Assets\\Sprites\\GCCloud1.png");
		m_sprites[4].SetSize(500 * deltaWidth, 242 * deltaHeight);
		m_sprites[4].SetPosition(80 * deltaWidth, 300 * deltaHeight);

		m_sprites[5].SetTexture(".\\Assets\\Sprites\\GCCloud4.png");
		m_sprites[5].SetSize(762 * deltaWidth, 360 * deltaHeight);
		m_sprites[5].SetPosition(80 * deltaWidth, 300 * deltaHeight);

		m_sprites[6].SetTexture(".\\Assets\\Sprites\\GCFront.png");
		m_sprites[6].SetSize(VideoManager::Get()->GetWidth(), VideoManager::Get()->GetHeight());

		break;
	case PIRATE:
		break;
	case PARTY:
		break;
	default:
		break;
	}
}
