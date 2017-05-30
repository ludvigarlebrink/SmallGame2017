#ifndef __LEVELSELECTOR_H__
#define __LEVELSELECTOR_H__


#include "InputManager.h"
#include "Level.h"
#include "LevelHandler.h"
#include "UIImage.h"


#include <string>



class LevelSelector
{
public:
	LevelSelector();
	virtual ~LevelSelector();

	void InitVisuals();
	void FreeVisuals();

	bool Update();
	
	//::.. GET FUNCTIONS ..:://
	std::string GetLevel();
	bool GetHasPlaylistEnded();
	bool GetVisualsInitialized();

	bool SaveQueue();

private:
	InputManager *				m_input;

	std::vector<UIText *>		m_playListText;
	Level						m_level;
	std::vector<std::string>	m_levelQueue;
	LevelHandler				m_levelHandler;
	UIImage						m_selectorImage;
	std::vector<UIText *>		m_levelChoice;

	std::vector<std::string>	m_levelText;

	int32_t						m_levelSelector;
	int32_t						m_currentLevel;
	int32_t						m_numLevels;

	bool						m_hasPlaylistEnded;
	bool						m_visualsInitialized;
	bool						m_playListSelected;

	uint32_t					m_numToShow;
	int32_t						m_levelInc;
	
};


#endif // !__LEVELSELECTOR_H__