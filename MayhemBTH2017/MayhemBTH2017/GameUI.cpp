#include "GameUI.h"


GameUI::GameUI()
{
	m_video = VideoManager::Get();

	m_numPlayers = 1;

	m_winnerText = new UIText;

	m_gameTimer = new UIText;
	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerScore[i] = new UIText;
	}

	m_winnerText->SetSize(60);
	m_winnerText->SetPosition(0, 150.0f);

	m_gameTimer->SetText("60");
	m_gameTimer->SetSize(46);
	m_gameTimer->SetPosition(0, -60 + m_video->GetHeight() / 2);
	m_gameTimer->SetColor(248, 238, 190);

	m_playerScore[0]->SetPosition((-0.75f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));
	m_playerScore[1]->SetPosition((-0.25f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));
	m_playerScore[2]->SetPosition((0.25f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));
	m_playerScore[3]->SetPosition((0.75f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));
				
	m_playerScore[0]->SetColor(252, 61, 73, 255);
	m_playerScore[1]->SetColor(255, 147, 73, 255);
	m_playerScore[2]->SetColor(61, 212, 66, 255);
	m_playerScore[3]->SetColor(43, 166, 160, 255);

	m_pauseDisplay = false;
	m_showWinner = false;

	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerScore[i]->SetSize(40);
		m_playerScore[i]->SetText("0");
	}
}


GameUI::~GameUI()
{
	delete m_gameTimer;
	
	for (uint32_t i = 0; i < 4; i++)
	{
		delete m_playerScore[i];
	}

	delete m_winnerText;
}


void GameUI::Update(float time)
{
	if (m_pauseDisplay)
	{
		for (uint32_t i = 0; i < 4; i++)
		{
			std::stringstream ss2;
			ss2 << std::fixed << std::setprecision(1) << ScoreManager::GetScore(i);
			std::string str2 = ss2.str();

			m_playerScore[i]->SetText(str2.c_str());

			m_playerScore[i]->Render();
		}

		if (m_showWinner)
		{
			int winner = ScoreManager::GetWinnerIndex();

			if (winner == 0)
			{
				m_winnerText->SetText("WINNER: PLAYER 1");
				m_winnerText->SetColor(252, 61, 73, 255);
			}
			else if (winner == 1)
			{
				m_winnerText->SetText("WINNER: PLAYER 2");
				m_winnerText->SetColor(255, 147, 73, 255);
			}
			else if (winner == 2)
			{
				m_winnerText->SetText("WINNER: PLAYER 3");
				m_winnerText->SetColor(61, 212, 66, 255);
			}
			else if (winner == 3)
			{
				m_winnerText->SetText("WINNER: PLAYER 4");
				m_winnerText->SetColor(43, 166, 160, 255);
			}

			m_winnerText->Render();
		}
	}
	else
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << time;
		std::string str = ss.str();
		m_gameTimer->SetText(str.c_str());
	
		for (uint32_t i = 0; i < 4; i++)
		{

			if (ScoreManager::GetGotScore(i))
			{
				m_playerScore[i]->SetScale(1.2f);
			}
			else if (m_playerScore[i]->GetScale() > 1.00001f)
			{
				m_playerScore[i]->SetScale(m_playerScore[i]->GetScale() - TimeManager::GetDeltaTime());
				if (m_playerScore[i]->GetScale() < 0.9999f)
				{
					m_playerScore[i]->SetScale(1.0f);
				}
			}
	
			std::stringstream ss2;
			ss2 << std::fixed << std::setprecision(1) << ScoreManager::GetScore(i);
			std::string str2 = ss2.str();
	
			m_playerScore[i]->SetText(str2.c_str());
	
			m_playerScore[i]->Render();
		}
	
		m_gameTimer->Render();
	}
}


void GameUI::SetNumPLayers(uint32_t numPlayers)
{
	m_numPlayers = numPlayers;
}


void GameUI::SetPauseDisplay(bool value)
{
	m_pauseDisplay = value;

	if (m_pauseDisplay)
	{
		m_playerScore[0]->SetPosition((-0.75f * m_video->GetWidth()) / 2, 0.0f);
		m_playerScore[1]->SetPosition((-0.25f * m_video->GetWidth()) / 2, 0.0f);
		m_playerScore[2]->SetPosition((0.25f * m_video->GetWidth()) / 2, 0.0f);
		m_playerScore[3]->SetPosition((0.75f * m_video->GetWidth()) / 2, 0.0f);

		m_playerScore[0]->SetScale(1.3f);
		m_playerScore[1]->SetScale(1.3f);
		m_playerScore[2]->SetScale(1.3f);
		m_playerScore[3]->SetScale(1.3f);
	}
	else
	{
		m_playerScore[0]->SetPosition((-0.75f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));
		m_playerScore[1]->SetPosition((-0.25f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));
		m_playerScore[2]->SetPosition((0.25f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));
		m_playerScore[3]->SetPosition((0.75f * m_video->GetWidth()) / 2, -35.0f + (m_video->GetHeight() / 2));

		m_playerScore[0]->SetScale(1.0f);
		m_playerScore[1]->SetScale(1.0f);
		m_playerScore[2]->SetScale(1.0f);
		m_playerScore[3]->SetScale(1.0f);
	}
}


void GameUI::SetShowWinner(bool value)
{
	m_showWinner = value;
}
