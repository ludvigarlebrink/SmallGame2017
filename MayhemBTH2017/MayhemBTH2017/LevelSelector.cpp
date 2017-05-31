#include "LevelSelector.h"



LevelSelector::LevelSelector()
{
	m_input = InputManager::Get();
	m_levelSelector = 0;
	m_currentLevel = 0;
	m_numLevels = 0;
	m_levelInc = 0;

	m_hasPlaylistEnded = false;
	m_visualsInitialized = false;
	m_playListSelected = false;
}


LevelSelector::~LevelSelector()
{

}


void LevelSelector::InitVisuals()
{
	m_playListText.resize(10);
	m_levelChoice.resize(10);
	m_levelHandler.GetLevelNames(m_levelText);

	m_numToShow;

	m_textLevels.SetText("Levels");
	m_textLevels.SetColor(229, 122, 16, 255);
	m_textLevels.SetPosition(-250, 275);
	m_textLevels.SetSize(60);

	m_textPlaylist.SetText("Playlist");
	m_textPlaylist.SetColor(229, 122, 16, 255);
	m_textPlaylist.SetPosition(250, 275);
	m_textPlaylist.SetSize(60);

	if (m_levelText.size() > 10)
	{
		m_numToShow = 10;
	}
	else
	{
		m_numToShow = m_levelText.size();
	}

	for (size_t i = 0; i < m_numToShow; i++)
	{
		m_levelChoice[i] = new UIText;
		m_levelChoice[i]->SetText(m_levelText[i].c_str());
		m_levelChoice[i]->SetPosition(-250, 200 - (50 * i));
		m_levelChoice[i]->SetColor(235, 235, 180, 255);
	}

	for (size_t i = 0; i < 10; ++i)
	{
		m_playListText[i] = new UIText;
		m_playListText[i]->SetText("");
		m_playListText[i]->SetPosition(250, 200 - (50 * i));
		m_playListText[i]->SetColor(235, 235, 180, 255);
	}

	m_visualsInitialized = true;
}


void LevelSelector::FreeVisuals()
{
	for (size_t i = 0; i < m_levelChoice.size(); i++)
	{
		delete m_levelChoice[i];
	}

	for (size_t i = 0; i < m_playListText.size(); i++)
	{
		delete m_playListText[i];
	}

	m_playListText.clear();
	m_levelChoice.clear();
	m_levelText.clear();

	m_visualsInitialized = false;
}


bool LevelSelector::Update()
{
	m_textLevels.Render();
	m_textPlaylist.Render();
	for (uint32_t i = 0; i < m_numToShow; i++)
	{
		if (i == m_levelSelector && !m_playListSelected)
		{
			m_levelChoice[i]->SetScale(1.3f);
		}
		else
		{
			m_levelChoice[i]->SetScale(1.0f);
		}
		
		m_levelChoice[i]->Render();
	}

	for (uint32_t i = 0; i < m_numLevels; ++i)
	{
		if (i == m_levelSelector && m_playListSelected)
		{
			m_playListText[i]->SetScale(1.3f);
		}
		else
		{
			m_playListText[i]->SetScale(1.0f);
		}

		m_playListText[i]->Render();
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_levelSelector > 0)
		{
			--m_levelSelector;
		}
		else if(m_levelInc > 0)
		{
			--m_levelInc;

			for (size_t i = 0; i < m_numToShow; i++)
			{
				m_levelChoice[i]->SetText(m_levelText[i + m_levelInc].c_str());
			}
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		if (!m_playListSelected)
		{
			if (static_cast<uint32_t>(m_levelSelector) < m_numToShow - 1)
			{
				++m_levelSelector;

				if (m_levelSelector > m_numToShow)
				{
					m_levelSelector = m_numToShow - 2;
				}
			}
			else if (0 < m_levelText.size() - 10 - m_levelInc && m_numToShow > 10)
			{
				++m_levelInc;

				for (size_t i = 0; i < m_numToShow; i++)
				{
					m_levelChoice[i]->SetText(m_levelText[i + m_levelInc].c_str());
				}
			}
		}
		else
		{
			if (static_cast<uint32_t>(m_levelSelector) + 1 < m_numLevels)
			{
				++m_levelSelector;
			}
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_X) && !m_playListSelected)
	{
		if (m_numLevels > 0)
		{
			--m_numLevels;
		}
	}

	if ((m_input->GetButtonDown(CONTROLLER_BUTTON_A) || 
		m_input->GetButtonDown(CONTROLLER_BUTTON_X)) && 
		m_playListSelected)
	{
		if (m_numLevels > 0)
		{
			for (uint32_t i = m_levelSelector; i < m_numLevels; ++i)
			{
				if (i == m_numLevels - 1)
				{
					m_playListText[i]->SetText("");
				}
				else
				{
					m_playListText[i]->SetText(m_playListText[i + 1]->GetText());
				}
			}

			--m_numLevels;

			if (m_levelSelector + 1 >= m_numLevels)
			{
				m_levelSelector = m_numLevels - 1;
			}

			if (m_numLevels <= 0)
			{
				m_playListSelected = false;
				m_levelSelector = 0;
			}
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A) && !m_playListSelected)
	{
		m_levelQueue.push_back(m_levelChoice[m_levelSelector]->GetText());

		if (m_numLevels < 10)
		{
			m_playListText[m_numLevels]->SetText(m_levelChoice[m_levelSelector]->GetText());
			++m_numLevels;
		}
	}

	if ((m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT) || m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
		&& m_numLevels > 0)
	{
		m_playListSelected = !m_playListSelected;

		if (!m_playListSelected)
		{
			if (m_levelSelector + 1 >= m_numToShow)
			{
				m_levelSelector = m_numToShow - 1;
			}
		}
		else
		{
			if (m_levelSelector + 1 >= m_numLevels)
			{
				m_levelSelector = m_numLevels - 1;
			}
		}
	}


	return false;
}


std::string LevelSelector::GetLevel()
{
	std::string level = m_levelQueue[m_currentLevel];
	++m_currentLevel;

	if (m_currentLevel >= m_numLevels)
	{
		m_currentLevel = 0;
		m_hasPlaylistEnded = true;
	}

	return level;
}


bool LevelSelector::GetHasPlaylistEnded()
{
	return m_hasPlaylistEnded;
}


bool LevelSelector::GetVisualsInitialized()
{
	return m_visualsInitialized;
}

bool LevelSelector::SaveQueue()
{
	if (m_numLevels <= 0)
	{
		return false;
	}

	m_levelQueue.clear();

	m_levelQueue.resize(m_numLevels);

	for (uint32_t i = 0; i < m_numLevels; i++)
	{
		m_levelQueue[i] = m_playListText[i]->GetText();
	}

	return true;
}
