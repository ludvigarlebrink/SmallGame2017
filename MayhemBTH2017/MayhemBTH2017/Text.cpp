#include "Text.h"



Text::Text()
{

	TTF_Init();
	m_text = "";
	m_size = 40;
}


Text::Text(const Text & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return;
	}
}


Text::~Text()
{
	// TODO
}


//::.. OPERATOR OVERLOADING ..:://
void Text::operator=(const Text & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return;
	}
}


void Text::operator=(const char * text)
{
	// TODO
}


bool Text::operator==(const Text & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return true;
	}

	return strcmp(m_text, object.m_text);
}


bool Text::operator==(const char * text)
{
	return strcmp(m_text, text);
}


//::.. UPDATE FUNCTIONS ..:://
void Text::Render()
{
	SDL_Color color;
	color.r = 255;
	color.g = 234;
	color.b = 150;
	color.a = 0;

	if (strlen(m_text) > 0)
	{
		TextToTexture(m_text, color, m_posX, m_posY, 70);
	}
}

bool Text::Enable(uint32_t component)
{
	return false;
}

bool Text::Disable(uint32_t component)
{
	return false;
}


//::.. GET FUNCTIONS ..:://
const char * Text::GetText() const
{
	return m_text;
}


int Text::GetPosX() const
{
	return m_posX;
}


int Text::GetPosY() const
{
	return m_posY;
}


int Text::GetSize() const
{
	return m_size;
}


//::.. SET FUNCTIONS ..:://
void Text::SetText(const char* text)
{
	m_text = text;
}

void Text::SetPositon(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Text::SetSize(int size)
{
	m_size = size;
}


void Text::SetColor(float r, float g, float b, float a)
{
	m_color.r = static_cast<uint8_t>(r * 255);
	m_color.g = static_cast<uint8_t>(g * 255);
	m_color.b = static_cast<uint8_t>(b * 255);
	m_color.a = static_cast<uint8_t>(a * 255);
}


void Text::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
}


void Text::SetAlpha(float alpha)
{
	m_color.a = static_cast<uint8_t>(alpha * 255);
}


void Text::SetAlpha(uint8_t alpha)
{
	m_color.a = alpha;
}


void Text::SetPivot(uint32_t pivot)
{
	m_pivot = pivot;
}

void Text::SetOutlineSize()
{
}

void Text::SetOutlineColor()
{
}


//::.. HELP FUNCTIONS ..:://
void Text::TextToTexture(std::string message, SDL_Color color, int x, int y, int size)
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

	TTF_Font * font = TTF_OpenFont(".\\Assets\\Fonts\\Snap.ttf", m_size);

	// OUTLINE
	SDL_Color black = { 0x00, 0x00, 0x00 };
	
	SDL_Surface * sFont = TTF_RenderText_Blended(font, message.c_str(), color);

	TTF_SetFontOutline(font, 2);
	SDL_Surface * sOutline = TTF_RenderText_Blended(font, message.c_str(), black);

	SDL_Rect rect = { 4, 2, sOutline->w, sOutline->h };


	SDL_BlitSurface(sFont, NULL, sOutline, &rect);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sOutline->w, sOutline->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sOutline->pixels);


	float halfHeight = m_Height / 2;
	float halfWidth = m_Width / 2;

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1); 
		glVertex2f(
			static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth)),
			y - ((sFont->h / 2) - halfHeight));

		glTexCoord2f(1, 1); 
		glVertex2f(static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth)),
			y - ((sFont->h / 2) - halfHeight));

		glTexCoord2f(1, 0); 
		glVertex2f(static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth)),
			y + ((sFont->h / 2) + halfHeight));

		glTexCoord2f(0, 0); 
		glVertex2f(static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth)),
			y + ((sFont->h / 2) + halfHeight));
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
	TTF_CloseFont(font);
	SDL_FreeSurface(sFont);
}