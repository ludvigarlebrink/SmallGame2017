#include "LevelImporter.h"

#include <iostream> //DEBUG

LevelImporter::LevelImporter()
{
	// Do nothing...
}


LevelImporter::~LevelImporter()
{
	// Do nothing...
}

void LevelImporter::ImportLevel(Level & level)
{
	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;

	std::ifstream m_fileName(".\\Assets\\Levels\\ExportTestLOL.mrlevel", std::ios::binary); //REPLACE WITH FILENAME

	uint32_t textureID[nrOfBlocks] = { 0 };
	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };
	uint32_t i = 0;

	m_fileName.read(reinterpret_cast<char*>(textureID), sizeof(uint32_t) * (level.SIZE_X * level.SIZE_Y));
	m_fileName.read(reinterpret_cast<char*>(isOccupied), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	m_fileName.read(reinterpret_cast<char*>(isSpawn), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));


	for (size_t x = 1; x < level.SIZE_X; x++)
	{
		for (size_t y = 1; y < level.SIZE_Y; y++)
		{

			level.SetTexture(x, y, textureID[i]);
			level.SetOccupied(x, y, isOccupied[i]);
			level.SetSpawnPoint(x, y, isSpawn[i]);

			if(isOccupied[i])
				level.AddBlock(x, y);

			i++;
		}
	}

	std::cout << "IMPORTED" << std::endl;

}


