#ifndef __LEVELEDITORLEVEL_H__
#define __LEVELEDITORLEVEL_H__


#include "Transform.h"
#include "AShader.h"
#include "Camera.h"
#include "Mesh.h"
#include "InputManager.h"


#include <glm.hpp>
#include <cstdint>
#include <string>
#include <vector>


class Level
{
public:
	const static int SIZE_X = 84;
	const static int SIZE_Y = 48;

	struct Block
	{
		uint32_t	textureID; // 4 bytes.
		bool		isOccupied; // 1 byte.
		bool		isSpawnPoint; // 1 byte.
		glm::vec2	uvCoord;
	};
	
	Level();
	virtual ~Level();
	
	void Render(Camera camera);

	//::.. MODIFY FUNCTIONS ..:://
	void AddBlock(uint32_t posX, uint32_t posY, glm::vec2 uv);
	void RemoveBlock(uint32_t posX, uint32_t posY);
	void AddSpawnPoint(uint32_t posX, uint32_t posY);

	//::.. GET FUNCTIONS ..:://
	bool GetIsOccupied(uint32_t posX, uint32_t posY);
	bool GetIsSpawnPoint(uint32_t posX, uint32_t posY);
	glm::vec2 GetTempUV(uint32_t posX, uint32_t posY);
	uint32_t GetTextureID(uint32_t posX, uint32_t posY);
	const std::string& GetName();

	//::.. SET FUNCTIONS ..:://
	void SetTexture(uint32_t posX, uint32_t posY, uint32_t textureID);
	void SetOccupied(uint32_t posX, uint32_t posY, bool isOccupied);
	void SetSpawnPoint(uint32_t posX, uint32_t posY, bool isSpawnPoint);
	void setUv(uint32_t posX, uint32_t posY, glm::vec2 uv);
	void SetName(const std::string& name);

	void Clear();

	void UpdateBlocks(uint32_t posX, uint32_t posY, bool isOccupied, glm::vec2 uv);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();
	void InitGrid();
	void InitMesh();


private:
	Block		m_grid[SIZE_X][SIZE_Y];
	
	std::string	m_name;

	Mesh		m_mesh;
	Vertex3D *	m_vertices;

	Mesh		m_mesh2;
	Vertex3D *	m_vertices2;

	AShader		m_debugShader;

	uint32_t	m_nrOfSpawnPoints;
	uint32_t	m_nrOfBlocks;

	InputManager *		m_input;
	glm::vec4			m_uv;


};


#endif // !__LEVELEDITORLEVEL_H__