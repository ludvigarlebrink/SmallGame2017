#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__


#include "TimeManager.h"
#include "UIImage.h"


#include <cstdint>
#include <vector>

class Background
{
public:
	enum BackgroundType
	{
		GRAND_CANYON = 0,
		PIRATE,
		PARTY
	};

	Background();
	virtual ~Background();

	void UpdateAndRender();

	void SetBackground(uint32_t backgroundType);
	static void SetIsPostNuclear(bool value);

private:
	//::.. HELP FUNCTIONS ..:://
	void UpdateGrandCanyon();
	void UpdatePirate();
	void UpdateParty();

	void InitBackground();


private:
	void Init();

private:
	enum Uniforms
	{
		TIME,
		RESOLUTION,
		ALPHA,
		NUM_UNIFORMS
	};

	GLuint m_shader;
	GLuint m_vao;
	GLuint m_buffer;
	GLuint m_uniforms[NUM_UNIFORMS];

	uint32_t m_backgroundType;
	std::vector<UIImage> m_sprites;
	static bool	m_isPostNuclear;

	float m_t;
};


#endif // !__BACKGROUND_H__