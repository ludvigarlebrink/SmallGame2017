#include "UIImage.h"


#include "VideoManager.h"


UIImage::UIImage()
{
	m_videoManager = VideoManager::Get();

	m_windowHeight = m_videoManager->GetHeight();
	m_windowWidth = m_videoManager->GetWidth();


	// TEMP
	m_posY = 0;
	m_posX = 0;
	m_color.r = 255;
	m_color.b = 255;
	m_color.g = 255;
	m_color.a = 255;

	m_sizeX = 600;
	m_sizeY = 500;


	m_showTexture = false;
	TextureHandler imp;
	m_texture = imp.Import(".\\Assets\\Sprites\\MainMenu.png");
}


UIImage::~UIImage()
{
}


void UIImage::Render()
{
	glUseProgram(0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// m_Width and m_Height is the resolution of window.
	glOrtho(0, m_windowWidth, 0, m_windowHeight, -1, 1);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	// FIX THIS !
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	
	int x = m_posX;
	int y = m_posY;
	
	SDL_Surface * surface = nullptr;

	if (m_showTexture)
	{
		m_texture.Bind();
	}
	else
	{
		surface = SDL_CreateRGBSurface(0, m_sizeX, m_sizeY, 32, rmask, gmask, bmask, amask);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, m_color.r, m_color.g, m_color.b, m_color.a));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	}



	float halfHeight = m_windowHeight / 2;
	float halfWidth = m_windowWidth / 2;

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1);
		glVertex2f(
			static_cast<GLfloat>(x - ((m_sizeX / 2) - halfWidth)),
			static_cast<GLfloat>(y - ((m_sizeY / 2) - halfHeight)));

		glTexCoord2f(1, 1);
		glVertex2f(
			static_cast<GLfloat>(x + ((m_sizeX / 2) + halfWidth)),
			static_cast<GLfloat>(y - ((m_sizeY / 2) - halfHeight)));

		glTexCoord2f(1, 0);
		glVertex2f(
			static_cast<GLfloat>(x + ((m_sizeX / 2) + halfWidth)),
			static_cast<GLfloat>(y + ((m_sizeY / 2) + halfHeight)));

		glTexCoord2f(0, 0);
		glVertex2f(
			static_cast<GLfloat>(x - ((m_sizeX / 2) - halfWidth)),
			static_cast<GLfloat>(y + ((m_sizeY / 2) + halfHeight)));
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDeleteTextures(1, &texture);
	SDL_FreeSurface(surface);
}

//::.. GET FUNCTIONS ..:://
int32_t UIImage::GetSizeX()
{
	return m_sizeX;
}

int32_t UIImage::GetSizeY()
{
	return m_sizeY;
}

int32_t UIImage::GetPosX()
{
	return m_posX;
}

int32_t UIImage::GetPosY()
{
	return m_posY;
}


//::.. SET FUNCTIONS ..:://
void UIImage::SetPosition(int32_t x, int32_t y)
{
	m_posX = x;
	m_posY = y;
}

void UIImage::SetSize(int32_t x, int32_t y)
{
	m_sizeX = x;
	m_sizeY = y;
}


void UIImage::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
}


void UIImage::SetAlpha(float alpha)
{
	m_color.a = static_cast<uint8_t>(alpha * 255);
}


void UIImage::SetAlpha(uint8_t alpha)
{
	m_color.a = alpha;
}

void UIImage::SetTexture(const char * filepath)
{
	TextureHandler imp;
	m_texture = imp.Import(filepath);
	m_showTexture = true;
}
