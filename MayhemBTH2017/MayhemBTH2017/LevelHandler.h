#ifndef __LEVELHANDLER_H__
#define __LEVELHANDLER_H__


#include "Level.h"


#include <fstream>
#include <vector>

class LevelHandler
{
public:
	LevelHandler();
	virtual ~LevelHandler();

	//::.. IMPORT/EXPORT ..:://
	void Import(Level & level);
	void Export(Level & level);
	bool ImportRegister();
	bool ExportRegister();

	

	//::.. MODIFY FUNCTIONS ..:://
	bool AddToRegister(Level * level);
	bool RemoveFromRegister(const char* name);
	bool RemoveFromRegisterAt(uint32_t index);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumLevels();
	uint32_t GetMaxNumLevels();
	Level * GetLoadedLevel();

private:
	struct LevelRegister
	{
		bool			isLoaded;
		std::string		name;
		Level*			level;
	};

	bool								m_noneIsLoaded;
	bool								m_regHasChanged;
	std::vector<LevelRegister>			m_register;
	uint32_t							m_loaded;
		
};

#endif // ! __LEVELIMPORTER_H__