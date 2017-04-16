#ifndef __VIRTUALKEYBOARD_H__
#define __VIRTUALKEYBOARD_H__


#include "UIImage.h"
#include "UIText.h"
#include "UITextField.h"
#include "Vector.h"
#include "InputManager.h"
#include "VideoManager.h"


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

	//::.. SET FUNCTIONS ..:://
	void SetTitle() const;

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
	static const int NUM_HELP = 6;


	InputManager * m_input;

	std::string m_inputString;
	UIText m_chars[NUM_CHARS];
	UIText m_title;
	UIText m_help[NUM_HELP];

	int32_t m_pos;

	int32_t m_nSize;
	int32_t m_hSize;

	int m_currentLayout;

	UIImage			m_fill;
	UIImage			m_background;
	UIImage			m_background2;
	UITextField		m_textField;

};


#endif