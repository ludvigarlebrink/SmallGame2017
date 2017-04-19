#ifndef __UIIMAGE_H__
#define __UIIMAGE_H__


#include "VideoManager.h"
#include "Mesh.h"
#include "TextureHandler.h"
#include "Texture.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <cstring>
#include <string>


class UIImage
{
public:
	UIImage();
	virtual ~UIImage();

	void Render();

	//::.. GET FUNCTIONS ..:://
	

	//::.. SET FUNCTIONS ..:://
	void SetPositon(int32_t x, int32_t y);
	void SetSize(int32_t x, int32_t y);
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	void SetAlpha(float alpha);
	void SetAlpha(uint8_t alpha);
	void SetTexture(const char* filepath);

private:
	VideoManager * m_videoManager;

	int32_t m_windowHeight;
	int32_t m_windowWidth;

	uint32_t m_sizeX;
	uint32_t m_sizeY;

	int32_t m_posX;
	int32_t m_posY;

	SDL_Color m_color;
	Texture m_texture;
	bool	m_showTexture;
};


#endif // ! __UIIMAGE_H__