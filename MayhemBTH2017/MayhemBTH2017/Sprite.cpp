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

void Sprite::createSprite(glm::vec2 pos, glm::vec2 scale)
{
	this->setColorLoc();

	this->setTexLoc();

	scale = 1.0f * scale;

	this->BB.x = (pos.x);
	this->BB.y = (pos.y);
	this->BB.z = ((pos.x) + (scale.x));
	this->BB.w = ((pos.y) + (scale.y));

	this->quad.vertArr[0].position = glm::vec2((pos.x ), pos.y );
	this->quad.vertArr[1].position = glm::vec2((pos.x ) + (scale.x ), pos.y );
	this->quad.vertArr[2].position = glm::vec2((pos.x ), (pos.y ) + (scale.y ));
	this->quad.vertArr[3].position = glm::vec2((pos.x ) + (scale.x ), (pos.y) + (scale.y));

	this->quad.vertArr[0].UV = glm::vec2(0.0, 0.0);
	this->quad.vertArr[1].UV = glm::vec2(1.0, 0.0);
	this->quad.vertArr[2].UV = glm::vec2(0.0, 1.0);
	this->quad.vertArr[3].UV = glm::vec2(1.0, 1.0);

	if (this->vbo_ID == 0)
	{
		glGenBuffers(1, &this->vbo_ID);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(this->quad.vertArr[0]), &this->quad.vertArr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), 0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertex), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::setColor(glm::vec3 color)
{
	this->quad.color = color;
}

void Sprite::sendColor()
{
	glUniform3f(this->colorLoc, this->quad.color.x, this->quad.color.y, this->quad.color.z);
}

bool Sprite::hovered() {
	int temp_mouse_x = 0;
	int temp_mouse_y = 0;

	SDL_GetMouseState(&temp_mouse_x, &temp_mouse_y);

	float mouse_x = ((float)temp_mouse_x) / (1600.0f);
	float mouse_y = ((float)temp_mouse_y) / (800.0f);

	if (mouse_x > this->BB.x && mouse_y > this->BB.y
		&& mouse_x < this->BB.x + this->BB.z
		&& mouse_y < this->BB.y + this->BB.w)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Sprite::setTexture(const std::string& filePath)
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
	glGenTextures(1, &this->quad.texture_ID);
	glBindTexture(GL_TEXTURE_2D, this->quad.texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, texture->format->BytesPerPixel, texture->w, texture->h, 0, textureFormat, GL_UNSIGNED_BYTE, texture->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glDisable(GL_TEXTURE_2D);

}

void Sprite::setTexture2(const std::string & filePath)
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

void Sprite::sendTexture()
{
	glUniform1i(this->texLoc, this->quad.texture_ID);
}

void Sprite::draw()
{
	glEnable(GL_TEXTURE_2D);
	Bind();

	sendColor();

	sendTexture();

	glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(this->quad.vertArr[0]), &this->quad.vertArr, GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);

	glDisable(GL_TEXTURE_2D);

}

void Sprite::update(glm::vec2 pos, glm::vec2 scale)
{
	this->quad.vertArr[0].position = pos;
	this->quad.vertArr[1].position = glm::vec2(pos.x + scale.x, pos.y);
	this->quad.vertArr[2].position = glm::vec2(pos.x , pos.y + scale.y);
	this->quad.vertArr[3].position = glm::vec2(pos.x + scale.x, pos.y + scale.y);
}

void Sprite::setColorLoc()
{
	this->colorLoc = glGetUniformLocation(GetProgramID(), "color");
}

void Sprite::setTexLoc()
{
	this->texLoc = glGetUniformLocation(GetProgramID(), "texture");;
}
