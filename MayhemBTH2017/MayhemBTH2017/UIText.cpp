﻿#include "UIText.h"



Mesh * UIText::m_mesh = nullptr;
GLuint UIText::m_program = 0;
GLuint UIText::m_uniforms[Uniforms::NUM_UNIFORMS] = { 0 };

UIText::UIText()
{
	// FIX! DEBUG! PUT THIS SOMEWHERE ELSE :)
	TTF_Init();
	m_text = "";
	m_size = 40;
	m_pivot = 0;
	m_font = ".\\Assets\\Fonts\\Snap.ttf";
	m_scale = 1.0f;
	m_texture = 0;
	m_hasUpdated = true;

	m_screenWidth = VideoManager::Get()->GetWidth();
	m_screenHeight = VideoManager::Get()->GetHeight();

	if (m_mesh == nullptr)
	{
		CreateMesh();
	}
	
	if (m_program == 0)
	{
		CreateShader();
	}
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
	glDeleteTextures(1, &m_texture);
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
	if (m_hasUpdated)
	{
		CreateText();
	}

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, m_texture);

	glUseProgram(m_program);
	glUniform1f(m_uniforms[SCREEN_WIDTH], static_cast<float>(m_screenWidth));
	glUniform1f(m_uniforms[SCREEN_HEIGHT], static_cast<float>(m_screenHeight));
	glUniform1f(m_uniforms[WIDTH], static_cast<float>(m_width));
	glUniform1f(m_uniforms[HEIGHT], static_cast<float>(m_height));
	glUniform1f(m_uniforms[POSITION_X], static_cast<float>(m_posX));
	glUniform1f(m_uniforms[POSITION_Y], static_cast<float>(m_posY));
	glUniform1f(m_uniforms[SCALE], static_cast<float>(m_scale));

	glUniform1i(m_uniforms[ALBEDO_MAP], 0);

	m_mesh->Render();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
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
	m_hasUpdated = true;
}


void UIText::SetPosition(int x, int y)
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

	m_hasUpdated = true;
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
	m_hasUpdated = true;
}


void UIText::SetOutlineSize()
{
}


void UIText::SetOutlineColor()
{
}


//::.. HELP FUNCTIONS ..:://
void UIText::CreateMesh()
{
	m_mesh = new Mesh;

	Vertex2D vert[6];
	vert[0].position = glm::vec2(-1.0f, -1.0f);
	vert[0].texCoords = glm::vec2(0.0f, 1.0f);
	vert[1].position = glm::vec2(1.0f, -1.0f);
	vert[1].texCoords = glm::vec2(1.0f, 1.0f);
	vert[2].position = glm::vec2(-1.0f, 1.0f);
	vert[2].texCoords = glm::vec2(0.0f, 0.0f);
	vert[3].position = glm::vec2(1.0f, -1.0f);
	vert[3].texCoords = glm::vec2(1.0f, 1.0f);
	vert[4].position = glm::vec2(-1.0f, 1.0f);
	vert[4].texCoords = glm::vec2(0.0f, 0.0f);
	vert[5].position = glm::vec2(1.0f, 1.0f);
	vert[5].texCoords = glm::vec2(1.0f, 0.0f);

	m_mesh->Load(vert, 6);
}


void UIText::CreateShader()
{
	std::string shaders[2];
	uint32_t types[2];

	shaders[0] = ".\\Assets\\GLSL\\SpriteShader.vert";
	shaders[1] = ".\\Assets\\GLSL\\SpriteShader.frag";

	types[0] = ShaderManager::VERT_SHADER;
	types[1] = ShaderManager::FRAG_SHADER;

	m_program = ShaderManager::CreateAndAttachShaders("SpriteShader", shaders, types, 2);

	glBindAttribLocation(m_program, 0, "Position");
	glBindAttribLocation(m_program, 1, "TexCoords");

	ShaderManager::LinkAndValidate("SpriteShader");

	m_uniforms[SCREEN_WIDTH] = glGetUniformLocation(m_program, "ScreenWidth");
	m_uniforms[SCREEN_HEIGHT] = glGetUniformLocation(m_program, "ScreenHeight");
	m_uniforms[WIDTH] = glGetUniformLocation(m_program, "Width");
	m_uniforms[HEIGHT] = glGetUniformLocation(m_program, "Height");
	m_uniforms[POSITION_X] = glGetUniformLocation(m_program, "PosX");
	m_uniforms[POSITION_Y] = glGetUniformLocation(m_program, "PosY");
	m_uniforms[SCALE] = glGetUniformLocation(m_program, "Scale");
	m_uniforms[ALBEDO_MAP] = glGetUniformLocation(m_program, "AlbedoMap");
}


void UIText::CreateText()
{
	if (m_texture != 0)
	{
		glDeleteTextures(1, &m_texture);
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	TTF_Font * font = TTF_OpenFont(m_font, m_size);

	// OUTLINE
	SDL_Color black = { 0x00, 0x00, 0x00, 0x00 };

	SDL_Surface * sFont = TTF_RenderText_Blended(font, m_text, m_color);

	TTF_SetFontOutline(font, 2);
	SDL_Surface * sOutline = TTF_RenderText_Blended(font, m_text, black);

	SDL_Rect rect = { 4, 2, sOutline->w, sOutline->h };

	SDL_BlitSurface(sFont, NULL, sOutline, &rect);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sOutline->w, sOutline->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sOutline->pixels);

	m_width = sOutline->w;
	m_height = sOutline->h;

	TTF_CloseFont(font);
	SDL_FreeSurface(sFont);
	SDL_FreeSurface(sOutline);
}
