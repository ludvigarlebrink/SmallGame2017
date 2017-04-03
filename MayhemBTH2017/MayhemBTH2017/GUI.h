#ifndef __GUI_H__
#define __GUI_H__

#include <SDL.h>

#include "MasterShader.h"
#include "Sprite.h"
#include "Vector.h"
#include "String.h"


class GUI : public AShader
{
public:
	GUI(const std::string & filename);
	virtual ~GUI();

	void AddSprite(Sprite sprite);

	void virtual Update();

	void virtual Render();

private:
	Vector<Sprite> m_spriteArr;
	Vector<Sprite> m_buttonArr;
	void virtual AddAttributeLocation();

};



#endif // !__GUI_H__
