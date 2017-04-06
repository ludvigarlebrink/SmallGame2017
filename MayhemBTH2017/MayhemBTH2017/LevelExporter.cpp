#include "LevelExporter.h"

LevelExporter::LevelExporter()
{
	// Do nothing...
}


LevelExporter::~LevelExporter()
{
	// Do nothing...
}

void LevelExporter::Export(Level & level)
{
	const int nrOfBlocks = level.SIZE_X * level.SIZE_Y;

	//In file: (hex) 20 means false, 01 means true for bool
	//In file: (binary) 00 means false, 01 means true
	std::ofstream m_fileName("ExportTestLOL.mrlevel", std::ios::binary); //REPLACE WITH FILENAME


	uint32_t textureID[nrOfBlocks] = { 0 };
	bool isOccupied[nrOfBlocks] = { 0 };
	bool isSpawn[nrOfBlocks] = { 0 };
	uint32_t i = 0;

	for (size_t x = 0; x < level.SIZE_X; x++)
	{
		for (size_t y = 0; y < level.SIZE_Y; y++)
		{
			textureID[i] = level.GetTextureID(x, y);
			isOccupied[i] = level.GetIsOccupied(x, y);
			isSpawn[i] = level.GetIsSpawnPoint(x, y);
			i++;
		}
	}

	m_fileName.write(reinterpret_cast<char*>(textureID), sizeof(uint32_t) * (level.SIZE_X * level.SIZE_Y));
	m_fileName.write(reinterpret_cast<char*>(isOccupied), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	m_fileName.write(reinterpret_cast<char*>(isSpawn), sizeof(bool) * (level.SIZE_X * level.SIZE_Y));
	std::cout << "EXPORTED" << std::endl;
}
