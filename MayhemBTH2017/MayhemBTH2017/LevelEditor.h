#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__


#include "LevelExporter.h"
#include "Transform.h"
#include "DebugShaderTech.h"
#include "Camera.h"
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
	void SetTexture(uint32_t textureID);
	void SetOccupied(bool isOccupied);
	void SetSpawnPoint(bool isSpawnPoint);

	void SaveLevel();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void InitGrid();
	void InitMeshes();

private:
	struct MeshObjects
	{
		Transform transform;
		Mesh mesh;
	};

	Block m_grid[SIZE_X][SIZE_Y];
	MeshObjects m_meshObjects[SIZE_X][SIZE_Y];
	uint32_t m_posX;
	uint32_t m_posY;
	
	AShader			m_debugShader;
	Camera			m_camera;
};

#endif // __LEVELEDITOR_H__