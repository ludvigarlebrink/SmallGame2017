#include "GUIImage.h"


#include "VideoManager.h"


GUIImage::GUIImage()
{
	m_Height = 720;
	m_Width = 1280;
}


GUIImage::~GUIImage()
{
}


void GUIImage::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// m_Width and m_Height is the resolution of window.
	gluOrtho2D(0, m_Width, 0, m_Height);
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

	// OUTLINE
	SDL_Color black = { 233, 100, 240 };
	SDL_Surface * surface = SDL_CreateRGBSurface(0, 600, 560, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 50, 50, 50));

	int x = 0;
	int y = 0;


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);


	float halfHeight = m_Height / 2;
	float halfWidth = m_Width / 2;

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1);
		glVertex2f(
			static_cast<GLfloat>(x - ((surface->w / 2) - halfWidth)),
			y - ((surface->h / 2) - halfHeight));

		glTexCoord2f(1, 1);
		glVertex2f(static_cast<GLfloat>(x + ((surface->w / 2) + halfWidth)),
			y - ((surface->h / 2) - halfHeight));

		glTexCoord2f(1, 0);
		glVertex2f(static_cast<GLfloat>(x + ((surface->w / 2) + halfWidth)),
			y + ((surface->h / 2) + halfHeight));

		glTexCoord2f(0, 0);
		glVertex2f(static_cast<GLfloat>(x - ((surface->w / 2) - halfWidth)),
			y + ((surface->h / 2) + halfHeight));
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
