#include "Sprite.h"



Sprite::Sprite()
{
}

Sprite::Sprite(const std::string& shader, bool geom, bool particles)
	: AShader(shader, geom, particles)
{
	this->vbo_ID = 0;
}

Sprite::~Sprite()
{
}

void Sprite::CreateSprite(glm::vec2 pos, glm::vec2 scale)
{



	glGenVertexArrays(1, &m_vao);

	this->setColorLoc();

	this->setTexLoc();

	scale = 1.0f * scale;

	m_quad.vertArr[0].position = glm::vec2((pos.x ), pos.y );
	m_quad.vertArr[1].position = glm::vec2((pos.x ) + (scale.x ), pos.y );
	m_quad.vertArr[2].position = glm::vec2((pos.x ), (pos.y ) + (scale.y ));
	m_quad.vertArr[3].position = glm::vec2((pos.x ) + (scale.x ), (pos.y) + (scale.y));

	m_quad.vertArr[0].UV = glm::vec2(0.0, 0.0);
	m_quad.vertArr[1].UV = glm::vec2(1.0, 0.0);
	m_quad.vertArr[2].UV = glm::vec2(0.0, 1.0);
	m_quad.vertArr[3].UV = glm::vec2(1.0, 1.0);

	glGenBuffers(1, &vbo_ID);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(GUIVertex), m_quad.vertArr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)(2 * sizeof(float)));


	glBindVertexArray(0);

}

void Sprite::SetColor(glm::vec3 color)
{
	this->m_quad.color = color;
}

void Sprite::SendColor()
{
	glUniform3f(this->colorLoc, this->m_quad.color.x, this->m_quad.color.y, this->m_quad.color.z);
}



void Sprite::SetTexture(const std::string& filePath)
{

	SDL_Surface* texture = SDL_LoadBMP(filePath.c_str());//TTF_RenderText_Solid(font, "Cdarja", color);

	GLenum textureFormat = 0;

	switch (texture->format->BytesPerPixel) {
	case 1:
		textureFormat = GL_ALPHA;
		break;
	case 3:     // no alpha channel
		if (texture->format->Rmask == 0x000000ff)
			textureFormat = GL_RGB;
		else
			textureFormat = GL_BGR;
		break;
	case 4:     // contains an alpha channel
		if (texture->format->Rmask == 0x000000ff)
			textureFormat = GL_RGBA;
		else
			textureFormat = GL_BGRA;
		break;
	default:
		// wtf
		break;
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &this->m_quad.texture_ID);
	glBindTexture(GL_TEXTURE_2D, this->m_quad.texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, texture->format->BytesPerPixel, texture->w, texture->h, 0, textureFormat, GL_UNSIGNED_BYTE, texture->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glDisable(GL_TEXTURE_2D);

}

void Sprite::SetTexture2(const std::string & filePath)
{
	SDL_Surface* texture2 = SDL_LoadBMP(filePath.c_str());//TTF_RenderText_Solid(font, "Cdarja", color);

	GLenum textureFormat2 = 0;

	switch (texture2->format->BytesPerPixel) {
	case 1:
		textureFormat2 = GL_ALPHA;
		break;
	case 3:     // no alpha channel
		if (texture2->format->Rmask == 0x000000ff)
			textureFormat2 = GL_RGB;
		else
			textureFormat2 = GL_BGR;
		break;
	case 4:     // contains an alpha channel
		if (texture2->format->Rmask == 0x000000ff)
			textureFormat2 = GL_RGBA;
		else
			textureFormat2 = GL_BGRA;
		break;
	default:
		// wtf
		break;
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &this->hoverTexID);
	glBindTexture(GL_TEXTURE_2D, this->hoverTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, texture2->format->BytesPerPixel, texture2->w, texture2->h, 0, textureFormat2, GL_UNSIGNED_BYTE, texture2->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glDisable(GL_TEXTURE_2D);
}

void Sprite::SendTexture()
{
	glUniform1i(this->texLoc, this->m_quad.texture_ID);
}

void Sprite::Render()
{

	//sendTexture();
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(this->m_quad.vertArr[0]), &this->m_quad.vertArr, GL_STATIC_DRAW);
	SendColor();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glBindVertexArray(0);

}

void Sprite::ModifyPos(glm::vec2 pos, glm::vec2 scale)
{
	this->m_quad.vertArr[0].position = pos;
	this->m_quad.vertArr[1].position = glm::vec2(pos.x + scale.x, pos.y);
	this->m_quad.vertArr[2].position = glm::vec2(pos.x , pos.y + scale.y);
	this->m_quad.vertArr[3].position = glm::vec2(pos.x + scale.x, pos.y + scale.y);

}

void Sprite::setColorLoc()
{
	this->colorLoc = glGetUniformLocation(GetProgramID(), "color");
}

void Sprite::setTexLoc()
{
	this->texLoc = glGetUniformLocation(GetProgramID(), "texture");;
}
