#ifndef __LEVELEDITORLEVEL_H__
#define __LEVELEDITORLEVEL_H__


#include "LevelExporter.h"
#include "Transform.h"
#include "DebugShaderTech.h"
#include "Camera.h"
#include "Mesh.h"


#include <glm.hpp>
#include <cstdint>


class Level
{
public:
	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;

	struct Block
	{
		uint32_t	textureID;
		bool		isOccupied;
		bool		isSpawnPoint;
	};

	Level();
	virtual ~Level();

	void Render(Camera camera);

	//::.. SET FUNCTIONS ..:://
	void SetTexture(uint32_t posX, uint32_t posY, uint32_t textureID);
	void SetOccupied(uint32_t posX, uint32_t posY, bool isOccupied);
	void SetSpawnPoint(uint32_t posX, uint32_t posY, bool isSpawnPoint);

	//::.. GET FUNCTIONS ..:://
	bool GetIsOccupied(uint32_t posX, uint32_t posY);
	bool GetIsSpawnPoint(uint32_t posX, uint32_t posY);
	uint32_t GetTextureID(uint32_t posX, uint32_t posY);

	//::.. ADD FUNCTIONS ..:://
	void AddBlock(uint32_t posX, uint32_t posY);
	void RemoveBlock(uint32_t posX, uint32_t posY);
	void AddSpawnPoint(uint32_t posX, uint32_t posY);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void InitGrid();
	void InitMesh();

	void UpdateIsOccupied(uint32_t posX, uint32_t posY, bool isOccupied);


private:
	struct MeshObjects
	{
		Transform transform;
		Mesh mesh;
	};

	Block m_grid[SIZE_X][SIZE_Y];
	MeshObjects m_meshObjects[SIZE_X][SIZE_Y];

	Mesh		m_mesh;
	Vertex *	m_vertices;

	Mesh		m_mesh2;
	Vertex *	m_vertices2;

	AShader		m_debugShader;

	uint32_t	m_nrOfSpawnPoints;
	uint32_t	m_nrOfBlocks;
};


#endif // __LEVELEDITORLEVEL_H__