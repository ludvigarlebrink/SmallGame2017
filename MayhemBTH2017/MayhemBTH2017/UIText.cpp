#include "UIText.h"



UIText::UIText()
{
	// FIX! DEBUG! PUT THIS SOMEWHERE ELSE :)
	TTF_Init();
	m_text = "";
	m_size = 40;
	m_pivot = 0;
	m_font = ".\\Assets\\Fonts\\Snap.ttf";
	m_scale = 1.0f;
}


UIText::UIText(const UIText & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return;
	}
}


UIText::~UIText()
{
	// TODO
}


//::.. OPERATOR OVERLOADING ..:://
void UIText::operator=(const UIText & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return;
	}
}


void UIText::operator=(const char * text)
{
	// TODO
}


bool UIText::operator==(const UIText & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return true;
	}

	return strcmp(m_text, object.m_text);
}


bool UIText::operator==(const char * text)
{
	return strcmp(m_text, text);
}


//::.. UPDATE FUNCTIONS ..:://
void UIText::Render()
{
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 0;

	if (strlen(m_text) > 0)
	{
		TextToTexture(m_text, m_color, m_posX, m_posY, m_size);
	}
}

bool UIText::Enable(uint32_t component)
{
	return false;
}

bool UIText::Disable(uint32_t component)
{
	return false;
}


//::.. GET FUNCTIONS ..:://
const char * UIText::GetText() const
{
	return m_text;
}


int UIText::GetPosX() const
{
	return m_posX;
}


int UIText::GetPosY() const
{
	return m_posY;
}


int UIText::GetSize() const
{
	return m_size;
}

float UIText::GetScale() const
{
	return m_scale;
}


//::.. SET FUNCTIONS ..:://
void UIText::SetText(const char* text)
{
	m_text = text;
}

void UIText::SetPositon(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void UIText::SetSize(int size)
{
	m_size = size;
}

void UIText::SetScale(float scale)
{
	m_scale = scale;
}


void UIText::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
}


void UIText::SetAlpha(uint8_t alpha)
{
	m_color.a = alpha;
}


void UIText::SetPivot(uint32_t pivot)
{
	m_pivot = pivot;
}

void UIText::SetFont(const char * filepath)
{
	m_font = filepath;
}

void UIText::SetOutlineSize()
{
}

void UIText::SetOutlineColor()
{
}


//::.. HELP FUNCTIONS ..:://
void UIText::TextToTexture(std::string message, SDL_Color color, int x, int y, int size)
{
	glUseProgram(0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// m_Width and m_Height is the resolution of window.
	glOrtho(0, m_width, 0, m_height, -1, 1);
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

	TTF_Font * font = TTF_OpenFont(m_font, m_size * m_scale);

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


	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;

	GLfloat offsetNegX = 0;
	GLfloat offsetPosX = 0;
	GLfloat offsetNegY = 0;
	GLfloat offsetPosY = 0;

	switch (m_pivot)
	{
	case CENTER:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case TOP:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case BOTTOM:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case LEFT:
		offsetNegX = static_cast<GLfloat>(x + halfWidth);
		offsetPosX = static_cast<GLfloat>(x + sFont->w + halfWidth);
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case RIGHT:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case TOP_LEFT:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case TOP_RIGHT:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case BOTTOM_LEFT:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	case BOTTOM_RIGHT:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	default:
		offsetNegX = static_cast<GLfloat>(x - ((sFont->w / 2) - halfWidth));
		offsetPosX = static_cast<GLfloat>(x + ((sFont->w / 2) + halfWidth));
		offsetNegY = static_cast<GLfloat>(y - ((sFont->h / 2) - halfHeight));
		offsetPosY = static_cast<GLfloat>(y + ((sFont->h / 2) + halfHeight));

		break;
	}

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1); 
		glVertex2f(
			offsetNegX,
			offsetNegY);

		glTexCoord2f(1, 1); 
		glVertex2f(
			offsetPosX,
			offsetNegY);

		glTexCoord2f(1, 0); 
		glVertex2f(
			offsetPosX,
			offsetPosY);

		glTexCoord2f(0, 0); 
		glVertex2f(
			offsetNegX,
			offsetPosY);
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
	SDL_FreeSurface(sOutline);
}