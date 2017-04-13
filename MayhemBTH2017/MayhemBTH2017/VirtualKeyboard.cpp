#include "VirtualKeyboard.h"



VirtualKeyboard::VirtualKeyboard()
{
	m_nSize = 60;
	m_hSize = 72;

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
	gui.Render();
	for (size_t i = 0; i < NUM_CHARS; i++)
	{
		if (i != m_pos)
		{
			m_chars[i].Render();
		}
	}

	m_chars[m_pos].Render();

	m_inputText.Render();
}

const char * VirtualKeyboard::GetString() const
{
	return nullptr;
}

void VirtualKeyboard::Init()
{
	m_input = InputManager::Get();

	SwitchLayout(ALPHABET);
	m_currentLayout = ALPHABET;
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
		m_inputText.SetText(m_inputString.c_str());
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_X))
	{
		if (m_inputString.length() > 0)
		{
			m_inputString.pop_back();
			m_inputText.SetText(m_inputString.c_str());
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_Y))
	{
		m_inputString.append(" ");
		m_inputText.SetText(m_inputString.c_str());
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_RB))
	{
		if (m_currentLayout == QWERTY)
		{
			SwitchLayout(ALPHABET);
			m_currentLayout = ALPHABET;
		}
		else if (m_currentLayout == ALPHABET)
		{
			SwitchLayout(QWERTY);
			m_currentLayout = QWERTY;

		}
	}
}


void VirtualKeyboard::SwitchLayout(int layout)
{
	char * alphabet[NUM_CHARS] =
	{
		"A", "B", "C", "D", "E", "F", "G", "1", "2", "3",	// 10. 
		"H", "I", "J", "K", "L", "M", "N", "4", "5", "6",
		"O", "P", "Q", "R", "S", "T", "U", "7", "8", "9",
		"V", "W", "X", "Y", "Z", ",", ".", "-", "0", "?" 
	};
	
	char * qwerty[NUM_CHARS] =
	{
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",	// 10. 
		"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
		"A", "S", "D", "F", "G", "H", "J", "K", "L", "-",
		"Z", "X", "C", "V", "B", "N", "M", ",", ".", "?" 
	};
	
	
	for (size_t i = 0; i < NUM_CHARS; i++)
	{
		if (layout == ALPHABET)
		{
			m_chars[i].SetText(alphabet[i]);
		}
		else if (layout == QWERTY)
		{
			m_chars[i].SetText(qwerty[i]);
		}

		m_chars[i].SetSize(m_nSize);

		if (i < 10)
		{
			m_chars[i].SetPositon(i * m_nSize - (4.5f * m_nSize) , 0);
		}
		else if (i >= 10 && i < 20)
		{
			m_chars[i].SetPositon(i * m_nSize - (9.5f * m_nSize) - (5 * m_nSize), -m_nSize);
		}
		else if (i >= 20 && i < 30)
		{
			m_chars[i].SetPositon(i * m_nSize - (19.5f * m_nSize) - (5 * m_nSize), -m_nSize * 2);
		}
		else
		{
			m_chars[i].SetPositon(i * m_nSize - (29.5f * m_nSize) - (5 * m_nSize), -m_nSize * 3);
		}
	}
	
	m_inputText.SetPositon(0, 60);
}