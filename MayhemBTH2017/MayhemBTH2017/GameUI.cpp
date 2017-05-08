#include "GameUI.h"


GameUI::GameUI()
{
	m_video = VideoManager::Get();

	m_numPlayers = 1;

	m_gameTimer = new UIText;

	m_gameTimer->SetText("60");
	m_gameTimer->SetSize(46);
	m_gameTimer->SetPosition(0, -60 + m_video->GetHeight() / 2);
	m_gameTimer->SetColor(248, 238, 190);

	m_playerName[0].SetText("PLAYER 1");
	m_playerName[1].SetText("PLAYER 2");
	m_playerName[2].SetText("PLAYER 3");
	m_playerName[3].SetText("PLAYER 4");

	m_playerScore[0].SetPosition((-0.75f * m_video->GetWidth()) / 2, 30 - (m_video->GetHeight() / 2));
	m_playerScore[1].SetPosition((-0.25f * m_video->GetWidth()) / 2, 30 - (m_video->GetHeight() / 2));
	m_playerScore[2].SetPosition((0.25f * m_video->GetWidth()) / 2, 30 - (m_video->GetHeight() / 2));
	m_playerScore[3].SetPosition((0.75f * m_video->GetWidth()) / 2, 30 - (m_video->GetHeight() / 2));

	m_playerScore[0].SetColor(248, 78, 78, 255);
	m_playerScore[1].SetColor(78, 248, 78, 255);
	m_playerScore[2].SetColor(248, 248, 78, 255);
	m_playerScore[3].SetColor(78, 78, 248, 255);

	m_playerName[0].SetPosition((-0.75f * m_video->GetWidth()) / 2, (60 - (m_video->GetHeight() / 2)));
	m_playerName[1].SetPosition((-0.25f * m_video->GetWidth()) / 2, (60 - (m_video->GetHeight() / 2)));
	m_playerName[2].SetPosition((0.25f * m_video->GetWidth()) / 2, (60 - (m_video->GetHeight() / 2)));
	m_playerName[3].SetPosition((0.75f * m_video->GetWidth()) / 2, (60 - (m_video->GetHeight() / 2)));

	m_playerName[0].SetColor(248, 78, 78, 255);
	m_playerName[1].SetColor(78, 248, 78, 255);
	m_playerName[2].SetColor(248, 248, 78, 255);
	m_playerName[3].SetColor(78, 78, 248, 255);

	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerScore[i].SetSize(40);
		m_playerScore[i].SetText("0");
		m_playerName[i].SetSize(20);
	}
}


GameUI::~GameUI()
{
}


void GameUI::Update(PlayerStats * stats, float time)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << time;
	std::string str = ss.str();
	m_gameTimer->SetText(str.c_str());

	// FIX THIS SHIIIT!
	m_gameTimer->Render();
}


void GameUI::Render()
{
	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerName[i].Render();
		m_playerScore[i].Render();
	}
}

void GameUI::SetNumPLayers(uint32_t numPlayers)
{

}
