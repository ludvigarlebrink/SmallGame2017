#pragma once
#include "AShader.h"
#include <glm\glm.hpp>
#include <SDL2\SDL.h>

struct GUIVertex
{
	glm::vec2 position;
	glm::vec2 UV;
};

struct GUIQuad
{
	GUIVertex vertArr[4];
	glm::vec3 color;
	GLuint texture_ID;

};

class Sprite : public AShader
{
public:
	Sprite();
	Sprite(const std::string& shader, bool geom, bool particles);
	virtual ~Sprite();

	void createSprite(glm::vec2 pos, glm::vec2 scale);

	void setColor(glm::vec3 color);

	void sendColor();

	bool hovered();

	void setTexture(const std::string& filePath);

	void setTexture2(const std::string& filePath2);

	void sendTexture();

	void draw();

	void update(glm::vec2 pos, glm::vec2 scale);

private:
	void setColorLoc();
	void setTexLoc();
	GUIQuad		quad;
	glm::vec4	BB;
	GLuint		vbo_ID;
	GLuint		colorLoc;
	GLuint		texLoc;
	GLuint		hoverTexID;

};

