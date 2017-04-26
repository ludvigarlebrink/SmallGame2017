#include "LevelHandler.h"


//::.. CONSTRUCTORS ..:://
LevelHandler::LevelHandler()
	: m_regHasChanged(false), m_noneIsLoaded(true)
{
	// Do nothing...
}


LevelHandler::~LevelHandler()
{
	// Do nothing...
}


//::.. IMPORT/EXPORT ..:://
void LevelHandler::Import(Level & level)
{
	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;

	std::ifstream file(".\\Assets\\Levels\\ExportTestLOL.mrlevel", std::ios::binary); //REPLACE WITH FILENAME

	uint32_t textureID[nrOfBlocks] = { 0 };
	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };
	uint32_t i = 0;

	file.read(reinterpret_cast<char*>(textureID), sizeof(uint32_t) * (level.SIZE_X * level.SIZE_Y));
	file.read(reinterpret_cast<char*>(isOccupied), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	file.read(reinterpret_cast<char*>(isSpawn), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));


	for (size_t x = 1; x < level.SIZE_X; x++)
	{
		for (size_t y = 1; y < level.SIZE_Y; y++)
		{

			level.SetTexture(x, y, textureID[i]);
			level.SetOccupied(x, y, isOccupied[i]);
			level.SetSpawnPoint(x, y, isSpawn[i]);

			if(isOccupied[i])
				level.AddBlock(x, y, 0);

			i++;
		}
	}

	file.close();
}


void LevelHandler::Export(Level & level)
{
	LevelRegister newRegister;
	newRegister.isLoaded = true;
	newRegister.name = level.GetName();
	newRegister.level = nullptr;
	m_register.push_back(newRegister);

	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;


	//TextureID: 4 bytes, isOccupised: 1 byte, isSpawn: 1 byte
	//In file: (hex) 20 means false, 01 means true for bool
	//In file: (binary) 00 means false, 01 means true
	std::ofstream file(".\\Assets\\Levels\\ExportTestLOL.mrlevel", std::ios::binary); //REPLACE WITH FILENAME


	uint32_t textureID[nrOfBlocks] = { 0 };
	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };
	uint32_t i = 0;


	for (size_t x = 1; x < level.SIZE_X; x++)
	{
		for (size_t y = 1; y < level.SIZE_Y; y++)
		{
			textureID[i] = level.GetTextureID(x, y);
			isOccupied[i] = level.GetIsOccupied(x, y);
			isSpawn[i] = level.GetIsSpawnPoint(x, y);
			i++;
		}
	}

	file.write(reinterpret_cast<char*>(textureID), sizeof(uint32_t) * (level.SIZE_X * level.SIZE_Y));
	file.write(reinterpret_cast<char*>(isOccupied), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	file.write(reinterpret_cast<char*>(isSpawn), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));

	file.close();
}


bool LevelHandler::ImportRegister()
{
	// Try to open the file.
	std::ifstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary);

	// Check if the file is open.
	if (!file.is_open())
	{
		return false;
	}

	// Check version.
	uint32_t version = 0;
	file.read(reinterpret_cast<char*>(&version), sizeof(uint32_t));

	// Version not supported.
	if (version < 1)
	{
		return false;
	}
	
	// Clear the current register.
	m_register.clear();

	// Check number of levels;
	uint32_t numLevels = 0;
	file.read(reinterpret_cast<char*>(&numLevels), sizeof(uint32_t));

	// Resize to fit the levels.
	m_register.resize(numLevels);

	// Loop through the level cache and read from file.
	for (uint32_t i = 0; i < numLevels; i++)
	{
		// Size of the file string.
		uint32_t stringSize = static_cast<uint32_t>(m_register[i].name.size());
		file.read(reinterpret_cast<char*>(&stringSize), sizeof(uint32_t));

		// The acual string.
		const char * string = m_register[i].name.c_str();
		file.read(reinterpret_cast<char*>(&string), sizeof(char) * stringSize);

		// Add to the register.
		m_register[i].name = string;
		m_register[i].level = nullptr;
	}

	// Close the file.
	file.close();

	return true;
}


bool LevelHandler::ExportRegister()
{
	// Check if there is anything to export.
	if (m_register.empty())
	{
		return false;
	}

	// Open the file.
	std::ofstream file(".\\Assets\\Levels\\Register.mrlevelreg", std::ios::binary);

	// Version.
	uint32_t version = 1;
	file.write(reinterpret_cast<char*>(&version), sizeof(uint32_t));

	// Number of levels.
	uint32_t numLevels = static_cast<uint32_t>(m_register.size());
	file.write(reinterpret_cast<char*>(&numLevels), sizeof(uint32_t));

	// Loop through the level cache and write to file.
	for (uint32_t i = 0; i < numLevels; i++)
	{
		// Size of the file string.
		uint32_t stringSize = static_cast<uint32_t>(m_register[i].name.length());

		std::cout << stringSize << std::endl;
		file.write(reinterpret_cast<char*>(&stringSize), sizeof(uint32_t));

		// Loop through the string and store each char in the file.
		for (uint32_t j = 0; j < stringSize; j++)
		{
			char c = m_register[i].name[j];
			file.write(reinterpret_cast<char*>(&c), sizeof(char));
		}
	}

	// Close the file.
	file.close();
	
	return true;
}


//::.. MODIFY FUNCTIONS ..:://
bool LevelHandler::AddToRegister(Level * level)
{
	return false;
}


uint32_t LevelHandler::GetNumLevels()
{
	return m_register.size();
}


//::.. GET FUNCTIONS ..:://
uint32_t LevelHandler::GetMaxNumLevels()
{
	return uint32_t();
}


Level * LevelHandler::GetLoadedLevel()
{
	if (m_noneIsLoaded)
	{
		return nullptr;
	}

	return m_register[m_loaded].level;
}