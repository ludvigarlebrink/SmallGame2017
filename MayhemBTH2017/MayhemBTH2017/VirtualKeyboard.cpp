#include "VirtualKeyboard.h"



VirtualKeyboard::VirtualKeyboard()
{
	m_nSize = 40;
	m_hSize = 60;

	Init();
	m_pos = 0;
	m_chars[m_pos].SetSize(m_hSize);

}


VirtualKeyboard::~VirtualKeyboard()
{
}

void VirtualKeyboard::Render()
{
	Input();
	for (size_t i = 0; i < NUM_CHARS; i++)
	{
		m_chars[i].Render();
	}
	m_s = ALPHABET;
	m_inputText.Render();
}

void VirtualKeyboard::Init()
{
	m_input = InputManager::Get();

	SwitchLayout(ALPHABET);
}

void VirtualKeyboard::Input()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_pos - 10 >= 0)
		{
			m_chars[m_pos].SetSize(m_nSize);
			m_pos -= 10;
			m_chars[m_pos].SetSize(m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		if (m_pos + 10 < NUM_CHARS)
		{
			m_chars[m_pos].SetSize(m_nSize);
			m_pos += 10;
			m_chars[m_pos].SetSize(m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	{
		if (m_pos - 1 >= 0)
		{
			m_chars[m_pos].SetSize(m_nSize);
			--m_pos;
			m_chars[m_pos].SetSize(m_hSize);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		if (m_pos + 1 < NUM_CHARS)
		{
			m_chars[m_pos].SetSize(m_nSize);
			++m_pos;
			m_chars[m_pos].SetSize(m_hSize);
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_inputString.append(m_chars[m_pos].GetText());
	//	const char * c = m_inputString.c_str();
		m_inputText.SetText(m_inputString.c_str());
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_X))
	{
		if (m_inputString.length() > 0)
		{
			m_inputString.pop_back();
			m_inputText.SetText(m_inputString.c_str());
		}
		//	const char * c = m_inputString.c_str();
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_Y))
	{
		m_inputString.append(" ");
		m_inputText.SetText(m_inputString.c_str());
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_RB))
	{
		if (m_s == QWERTY)
		{
			SwitchLayout(ALPHABET);
			m_s = ALPHABET;
		}
		else if (m_s == ALPHABET)
		{
			SwitchLayout(QWERTY);
			m_s = ALPHABET;

		}
	}
}


void VirtualKeyboard::SwitchLayout(int t)
{
	char * alphabet[40] = 
	{
		"A", "B", "C", "D", "E", "F", "G", "1", "2", "3",	// 10. 
		"H", "I", "J", "K", "L", "M", "N", "4", "5", "6",
		"O", "P", "Q", "R", "S", "T", "U", "7", "8", "9",
		"V", "W", "X", "Y", "Z", ",", ".", "-", "0", "?" 
	};
	
	char * qwerty[40] = 
	{
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",	// 10. 
		"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
		"A", "S", "D", "F", "G", "H", "J", "K", "L", "-",
		"Z", "X", "C", "V", "B", "N", "M", ",", ".", "?" 
	};
	
	
	for (size_t i = 0; i < 40; i++)
	{
		if (t == ALPHABET)
		{
			m_chars[i].SetText(alphabet[i]);
		}
		else
		{
			m_chars[i].SetText(qwerty[i]);
		}

		m_chars[i].SetSize(m_nSize);

		if (i < 10)
		{
			m_chars[i].SetPositon(i * 40 - (5 * 40), 0);
		}
		else if (i >= 10 && i < 20)
		{
			m_chars[i].SetPositon(i * 40 - (10 * 40) - (5 * 40), -40);
		}
		else if (i >= 20 && i < 30)
		{
			m_chars[i].SetPositon(i * 40 - (20 * 40) - (5 * 40), -80);
		}
		else
		{
			m_chars[i].SetPositon(i * 40 - (30 * 40) - (5 * 40), -120);
		}
	}
	
	m_inputText.SetPositon(0, 60);
}