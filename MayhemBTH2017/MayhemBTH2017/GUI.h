#ifndef __GUI_H__
#define __GUI_H__

#include <SDL.h>

#include "AShader.h"
#include "Sprite.h"
#include "Vector.h"
#include "String.h"


class GUI : public AShader
{
public:
	GUI(const std::string & filename, bool geom);
	virtual ~GUI();

	void AddSprite(Sprite sprite);

	void Update();

	void Render();

private:
	Vector<Sprite> m_spriteArr;
	Vector<Sprite> m_buttonArr;
	void AddAttributeLocation();

};



#endif // !__GUI_H__
