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
	m_fill.Render();
	m_background.Render();
	m_background2.Render();
	m_textField.Render();
	m_title.Render();

	for (size_t i = 0; i < NUM_CHARS; i++)
	{
		if (i != m_pos)
		{
			m_chars[i].Render();
		}
	}

	for (size_t i = 0; i < NUM_HELP; i++)
	{
		m_help[i].Render();
	}

	m_chars[m_pos].Render();
}

void VirtualKeyboard::Reset()
{
	m_pos = 0;
	m_inputString = "";
}


const char * VirtualKeyboard::GetString() const
{
	return m_inputString.c_str();
}

void VirtualKeyboard::SetString(std::string text)
{
	m_inputString = text;
}


void VirtualKeyboard::Init()
{
	m_input = InputManager::Get();
	VideoManager * vm = VideoManager::Get();

	// THE BACKGROUND
	m_fill.SetSize(vm->GetWidth(), vm->GetHeight());
	m_fill.SetColor(0, 0, 0, 170);

	m_background.SetColor(50, 50, 50);
	m_background.SetSize(600, 440);

	m_background2.SetColor(150, 150, 150);
	m_background2.SetPosition(0, -80);
	m_background2.SetSize(600, 280);


	m_title.SetText("LEVEL NAME");
	m_title.SetSize(80);
	m_title.SetPosition(-280, 145);
	m_title.SetFont(".\\Assets\\Fonts\\steelfish.ttf");
	m_title.SetPivot(UIText::LEFT);
	m_title.SetColor(255, 255, 255, 255);

	m_help[0].SetText("A SELECT");
	m_help[1].SetText("B BACK");
	m_help[2].SetText("X BACKSPACE");
	m_help[3].SetText("Y SPACE");
	m_help[4].SetText("RB SWITCH LAYOUT");
	m_help[5].SetText("S DONE");

	for (size_t i = 0; i < NUM_HELP; i++)
	{
		m_help[i].SetPivot(UIText::LEFT);
		m_help[i].SetPosition(320, (i * -40) + 20 );
		m_help[i].SetFont(".\\Assets\\Fonts\\steelfish.ttf");
		m_help[i].SetColor(255, 255, 255, 255);
	}


	SwitchLayout(ALPHABET);
	m_currentLayout = ALPHABET;
	m_chars[m_pos].SetColor(255.0, 0.0, 0.0, 128);
}

void VirtualKeyboard::Input()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		if (m_pos - 10 >= 0)
		{
			m_chars[m_pos].SetColor(255, 255, 255, 255);
			m_chars[m_pos].SetSize(m_nSize);
			m_pos -= 10;
			m_chars[m_pos].SetSize(m_hSize);
			m_chars[m_pos].SetColor(255, 0, 0, 128);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		if (m_pos + 10 < NUM_CHARS)
		{
			m_chars[m_pos].SetColor(255, 255, 255, 255);
			m_chars[m_pos].SetSize(m_nSize);
			m_pos += 10;
			m_chars[m_pos].SetSize(m_hSize);
			m_chars[m_pos].SetColor(255, 0, 0, 128);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_LEFT))
	{
		if (m_pos - 1 >= 0)
		{
			m_chars[m_pos].SetColor(255, 255, 255, 255);
			m_chars[m_pos].SetSize(m_nSize);
			--m_pos;
			m_chars[m_pos].SetSize(m_hSize);
			m_chars[m_pos].SetColor(255, 0, 0, 128);
		}
	}
	else if (m_input->GetButtonDown(CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		if (m_pos + 1 < NUM_CHARS)
		{
			m_chars[m_pos].SetColor(255, 255, 255, 255);
			m_chars[m_pos].SetSize(m_nSize);
			++m_pos;
			m_chars[m_pos].SetSize(m_hSize);
			m_chars[m_pos].SetColor(255, 0, 0, 128);
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_inputString.append(m_chars[m_pos].GetText());
		m_textField.SetText(m_inputString.c_str());
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_X))
	{
		if (m_inputString.length() > 0)
		{
			m_inputString.pop_back();
			m_textField.SetText(m_inputString.c_str());
		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_Y))
	{
		m_inputString.append(" ");
		m_textField.SetText(m_inputString.c_str());
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_RIGHTBUTTON))
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
			m_chars[i].SetPosition(i * m_nSize - (4.5f * m_nSize) , 0);
		}
		else if (i >= 10 && i < 20)
		{
			m_chars[i].SetPosition(i * m_nSize - (9.5f * m_nSize) - (5 * m_nSize), -m_nSize);
		}
		else if (i >= 20 && i < 30)
		{
			m_chars[i].SetPosition(i * m_nSize - (19.5f * m_nSize) - (5 * m_nSize), -m_nSize * 2);
		}
		else
		{
			m_chars[i].SetPosition(i * m_nSize - (29.5f * m_nSize) - (5 * m_nSize), -m_nSize * 3);
		}

		m_chars[i].SetFont(".\\Assets\\Fonts\\steelfish.ttf");
		m_chars[i].SetColor(255, 255, 255, 255);
	}

	m_chars[m_pos].SetSize(m_hSize);
}