#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__


#include <string>


class Playlist
{
public:
	Playlist();
	virtual ~Playlist();

private:
	enum ScoreMode
	{
		DEATHMATCH = 0,
		KING_OF_THE_KILL,
		HOLD_THE_SKULL,
		MISSIONS
	};

	struct LevelInfo
	{
		std::string level;

		uint32_t	time;

		uint8_t		powerUpsSpawnRate;
		uint8_t		rareSpawnChance;
		uint8_t		gravityModifier;

		uint8_t		respawn;
		uint8_t		life;

		bool		instantDeath;
		bool		noRespawns;
		bool		immortality;

		bool		flippedCameraX;
		bool		flippedCameraY;
		bool		flippedControllsX;
		bool		flippedControllsY;
	};
	
	std::string		m_name;
	bool			m_sameSettingsOnAllLevels;
	bool			m_randomOrder;
};


#endif