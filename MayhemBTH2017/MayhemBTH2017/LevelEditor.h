#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "LevelExporter.h"
#include "Mesh.h"

#include <glm.hpp>
#include <cstdint>


class LevelEditor
{
public:
	const static int SIZE_X = 16;
	const static int SIZE_Y = 16;

	struct Block
	{
		uint32_t	textureID;
		bool		isOccupied;
		bool		isSpawnPoint;
	};

	//::.. CONSTRUCTORS ..:://
	LevelEditor();
	virtual ~LevelEditor();

	void Update();

	//::.. SET FUNCTIONS ..:://
	void SetTexture(uint32_t posX, uint32_t posY);
	void SetOccupied(uint32_t posX, uint32_t posY);
	void SetSpawnPoint(uint32_t posX, uint32_t posY);

	void SaveLevel();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	Block m_grid[SIZE_X][SIZE_Y];
	Mesh m_meshes[SIZE_X][SIZE_Y];
	uint32_t m_posX;
	uint32_t m_posY;
	
};

#endif // __LEVELEDITOR_H__