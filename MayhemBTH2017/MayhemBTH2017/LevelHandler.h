#ifndef __LEVELHANDLER_H__
#define __LEVELHANDLER_H__


#include "Level.h"
#include "LevelEditorPropPlacer.h"


#include <fstream>
#include <vector>

	struct PropsExport
	{
		uint32_t	id;
		glm::vec2	pos;
		float		rot;
	};

class LevelHandler
{
public:

	LevelHandler();
	virtual ~LevelHandler();

	//::.. IMPORT/EXPORT ..:://
	void Init();
	void Import(Level & level, uint32_t id);
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

private:
	uint32_t							m_nrOfMaps[1];
	std::string							m_names[3];
	uint32_t							m_size;
	uint32_t							m_mapSize;
	uint32_t							m_width = 84;
	uint32_t							m_height = 48;
	char*								m_dataBuffer;
};

#endif // ! __LEVELIMPORTER_H__