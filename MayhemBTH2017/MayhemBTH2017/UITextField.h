#ifndef __UITEXTFIELD_H__
#define __UITEXTFIELD_H__


#include "UIText.h"
#include "UIImage.h"


#include <cstdint>
#include <string>


class UITextField
{
public:
	UITextField();
	virtual ~UITextField();

	void Render();

	//::.. SET FUNCTIONS ..:://
	void SetText(const char* text);
	void SetPos(int32_t x, int32_t y);


private:
	UIText	m_text;
	UIImage	m_field;
	UIImage	m_background;

	int32_t m_posX;
	int32_t m_posY;
};


#endif