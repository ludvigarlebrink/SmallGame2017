#ifndef __UIIMAGE_H__
#define __UIIMAGE_H__


#include "VideoManager.h"
#include "Mesh.h"
#include "TextureHandler.h"
#include "Texture.h"
#include "ShaderManager.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <cstring>
#include <string>


class UIImage
{
public:
	UIImage();
	virtual ~UIImage();
	void PTest();

	//::.. UPDATE FUNCTIONS ..:://
	void Render();
	void RenderWithUV();


	//::.. GET FUNCTIONS ..:://
	int32_t GetSizeX();
	int32_t GetSizeY();
	float GetPosX();
	float GetPosY();
	Texture GetTexture();
	glm::vec2 GetUV();

	//::.. SET FUNCTIONS ..:://
	void SetPosition(float x, float y);
	void SetSize(int32_t x, int32_t y);
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	void SetAlpha(float alpha);
	void SetAlpha(uint8_t alpha);
	void SetTexture(const char* filepath);
	void SetTexture(Texture texture);
	void SetUV(glm::vec2 uv);

private:
	//::.. HELP FUNCTIONS ..:://
	void CreateMesh();
	void CreateShader();
	void CreateTexture();

private:
	enum Uniforms
	{
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		WIDTH,
		HEIGHT,
		POSITION_X,
		POSITION_Y,
		SCALE,
		ALBEDO_MAP,
		NUM_UNIFORMS
	};

	VideoManager * m_videoManager;

	int32_t m_windowHeight;
	int32_t m_windowWidth;

	uint32_t m_sizeX;
	uint32_t m_sizeY;

	float m_posX;
	float m_posY;

	glm::vec2 m_UV;	

	SDL_Color	m_color;
	Texture		m_texture;
	bool		m_showTexture;
	bool		m_temp = false;

	static Mesh *	m_mesh;	// Shader program.
	static GLuint	m_program;
	static GLuint	m_uniforms[NUM_UNIFORMS];
};


#endif // ! __UIIMAGE_H__