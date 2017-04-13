#ifndef __VIRTUALKEYBOARD_H__
#define __VIRTUALKEYBOARD_H__


#include "GUIImage.h"
#include "Text.h"
#include "Vector.h"
#include "InputManager.h"

#include <string>


class VirtualKeyboard
{
public:
	VirtualKeyboard();
	virtual ~VirtualKeyboard();

	void Enable();
	void Disable();

	void Update();
	void Render();

	//::.. GET FUNCTIONS ..:://
	const char* GetString() const;

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void Input();

	void SwitchLayout(int layout);

private:
	enum InputLayout
	{
		QWERTY = 0,
		ALPHABET
	};

	static const int NUM_CHARS = 40;

	InputManager * m_input;

	std::string m_inputString;
	Text m_chars[NUM_CHARS];
	Text m_inputText;

	int32_t m_pos;

	int32_t m_nSize;
	int32_t m_hSize;

	int m_currentLayout;

	GUIImage gui;

};


#endif