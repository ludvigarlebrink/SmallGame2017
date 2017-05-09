#include "GameSettings.h"



GameSettings::GameSettings()
{
	m_currSel = 0;

	m_gameLength = 60;
	m_powerUpsSpawnRate = 4;
	m_randomizedOrder = false;
	m_instantKills = false;

	m_input = InputManager::Get();
}


GameSettings::~GameSettings()
{
}

void GameSettings::CreateUI()
{
	VideoManager * vm = VideoManager::Get();

	m_ui = new UIText[NUM_SETTINGS];
	m_uiV = new UIText[NUM_SETTINGS];

	m_ui[0].SetText("Game Length");
	m_ui[1].SetText("Power Ups Spawn Rate");
	m_ui[2].SetText("Ranomized Level Order");
	m_ui[3].SetText("Instant Kills");

	m_ui[0].SetColor(235, 235, 180, 255);
	m_ui[1].SetColor(235, 235, 180, 255);
	m_ui[2].SetColor(235, 235, 180, 255);
	m_ui[3].SetColor(235, 235, 180, 255);

	m_ui[0].SetPosition(0, 200);
	m_ui[1].SetPosition(0, 120);
	m_ui[2].SetPosition(0, 40);
	m_ui[3].SetPosition(0, -40);

	m_ui[0].SetSize(24);
	m_ui[1].SetSize(24);
	m_ui[2].SetSize(24);
	m_ui[3].SetSize(24);

	m_uiV[0].SetText("60");
	m_uiV[1].SetText("x4");
	m_uiV[2].SetText("NO");
	m_uiV[3].SetText("NO");

	m_uiV[0].SetColor(235, 235, 180, 255);
	m_uiV[1].SetColor(170, 170, 170, 255);
	m_uiV[2].SetColor(170, 170, 170, 255);
	m_uiV[3].SetColor(170, 170, 170, 255);

	m_uiV[0].SetPosition(0, 165);
	m_uiV[1].SetPosition(0, 85);
	m_uiV[2].SetPosition(0, 5);
	m_uiV[3].SetPosition(0, -85);

	m_uiV[0].SetSize(40);
	m_uiV[1].SetSize(40);
	m_uiV[2].SetSize(40);
	m_uiV[3].SetSize(40);
}


void GameSettings::FreeUI()
{
}


void GameSettings::Update()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		m_uiV[m_currSel].SetColor(170, 170, 170, 255);

		--m_currSel;

		if (m_currSel < 0)
		{
			m_currSel = 0;
		}

		m_uiV[m_currSel].SetColor(235, 235, 180, 255);
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		m_uiV[m_currSel].SetColor(170, 170, 170, 255);

		++m_currSel;

		if (m_currSel >= NUM_SETTINGS)
		{
			m_currSel = NUM_SETTINGS - 1;
		}

		m_uiV[m_currSel].SetColor(235, 235, 180, 255);
	}

	switch (m_currSel)
	{
	case GAME_LENGTH:

		if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT) || m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
			{
				m_gameLength -= 30;

				if (m_gameLength < 30)
				{
					m_gameLength = 30;
				}
			}
			else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
			{
				m_gameLength += 30;

				if (m_gameLength > 300)
				{
					m_gameLength = 300;
				}
			}

			if (m_gameLength == 30)
			{
				m_uiV[GAME_LENGTH].SetText("30");
			}
			else if (m_gameLength == 60)
			{
				m_uiV[GAME_LENGTH].SetText("60");
			}
			else if (m_gameLength == 90)
			{
				m_uiV[GAME_LENGTH].SetText("90");
			}
			else if (m_gameLength == 120)
			{
				m_uiV[GAME_LENGTH].SetText("120");
			}
			else if (m_gameLength == 150)
			{
				m_uiV[GAME_LENGTH].SetText("150");
			}
			else if (m_gameLength == 180)
			{
				m_uiV[GAME_LENGTH].SetText("180");
			}
			else if (m_gameLength == 210)
			{
				m_uiV[GAME_LENGTH].SetText("210");
			}
			else if (m_gameLength == 240)
			{
				m_uiV[GAME_LENGTH].SetText("240");
			}
			else if (m_gameLength == 270)
			{
				m_uiV[GAME_LENGTH].SetText("270");
			}
			else
			{
				m_uiV[GAME_LENGTH].SetText("300");
			}
		}
		
		break;

	case POWER_UP_SPAWN_RATE:
		if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT) || m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
			{
				--m_powerUpsSpawnRate;

				if (m_powerUpsSpawnRate < 0)
				{
					m_powerUpsSpawnRate = 0;
				}
			}
			else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
			{
				++m_powerUpsSpawnRate;

				if (m_powerUpsSpawnRate > 8)
				{
					m_powerUpsSpawnRate = 8;
				}
			}

			if (m_powerUpsSpawnRate == 0)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("NO POWER UPS");
			}
			else if (m_powerUpsSpawnRate == 1)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x1");
			}
			else if (m_powerUpsSpawnRate == 2)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x2");
			}
			else if (m_powerUpsSpawnRate == 3)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x3");
			}
			else if (m_powerUpsSpawnRate == 4)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x4");
			}
			else if (m_powerUpsSpawnRate == 5)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x5");
			}
			else if (m_powerUpsSpawnRate == 6)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x6");
			}
			else if (m_powerUpsSpawnRate == 7)
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x7");
			}
			else
			{
				m_uiV[POWER_UP_SPAWN_RATE].SetText("x8");
			}
		}
		break;

	case RANDOMIZED_ORDER:
		if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT) || m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			m_randomizedOrder = !m_randomizedOrder;

			if (m_randomizedOrder)
			{
				m_uiV[RANDOMIZED_ORDER].SetText("YES");
			}
			else
			{
				m_uiV[RANDOMIZED_ORDER].SetText("NO");
			}
		}
		break;

	case INSTANT_KILLS:
		if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT) || m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			m_instantKills = !m_instantKills;

			if (m_instantKills)
			{
				m_uiV[INSTANT_KILLS].SetText("YES");
			}
			else
			{
				m_uiV[INSTANT_KILLS].SetText("NO");
			}
		}
		break;

	default:
		break;
	}
}


void GameSettings::Render()
{
	for (uint32_t i = 0; i < NUM_SETTINGS; i++)
	{
		m_ui[i].Render();
		m_uiV[i].Render();
	}
}


int32_t GameSettings::GetGameLenght()
{
	return m_gameLength;
}


int32_t GameSettings::GetPowerUpSpawnRate()
{
	return m_powerUpsSpawnRate;
}


bool GameSettings::GetRandomizedOrder()
{
	return false;
}
