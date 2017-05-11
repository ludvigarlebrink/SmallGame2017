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

private:
	//::.. HELP FUNCTIONS ..:://
	void UpdateGrandCanyon();
	void UpdatePirate();
	void UpdateParty();

	void InitBackground();

private:
	uint32_t m_backgroundType;
	std::vector<UIImage> m_sprites;
};


#endif // !__BACKGROUND_H__