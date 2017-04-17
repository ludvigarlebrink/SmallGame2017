#ifndef __UITEXT_H__
#define __UITEXT_H__


#include "Mesh.h"
#include "SDL.h"
#include "SDL_ttf.h"


#include <cstring>
#include <string>


class UIText
{
public:
	enum Pivot
	{
		CENTER = 0,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

	enum Compontent
	{
		OUTLINE,
		SHADOWS,
		GRADIENT
	};

	//::.. CONSTRUCTORS ..:://
	UIText();						// Default constructor.
	UIText(const UIText& object);	// Copy constructor.
	virtual ~UIText();				// Destructor.

	//::.. OPERATOR OVERLOADING ..:://
	void operator=(const UIText& object);
	void operator=(const char* text);
	bool operator==(const UIText& object);
	bool operator==(const char* text);

	//::.. UPDATE FUNCTIONS .:://
	void Render();

	//::.. MODIFY FUNCTIONS ..:://
	bool Enable(uint32_t component);
	bool Disable(uint32_t component);

	//::.. GET FUNCTIONS ..:://
	const char* GetText() const;
	int32_t GetPosX() const;
	int32_t GetPosY() const;
	int32_t GetSize() const;
	float GetScale() const;


	//::.. SET FUNCTIONS ..:://
	void SetText(const char* text);
	void SetPositon(int x, int y);
	void SetSize(int size);
	void SetScale(float scale);
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	void SetAlpha(uint8_t alpha);
	void SetPivot(uint32_t pivot);
	void SetFont(const char* filepath);

	void SetOutlineSize();
	void SetOutlineColor();



private:
	//::.. HELP FUNCTIONS .:://
	void TextToTexture(std::string message, SDL_Color color, int x, int y, int size);
	void Copy(const UIText& object);

private:
	GLuint stringTex = 0;
	GLuint tex;

	const char* m_text;
	const char* m_font;

	SDL_Color	m_color;
	int32_t		m_width = 1280;
	int32_t		m_height = 720;
	int32_t		m_posX;
	int32_t		m_posY;
	int32_t		m_size;
	float		m_scale;

	uint32_t m_pivot;

	bool m_hasOutlining;
	bool m_hasShadows;
	bool m_hasGradient;
};


#endif // ! __UITEXT_H__