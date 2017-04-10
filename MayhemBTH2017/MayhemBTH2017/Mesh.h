#ifndef __MESH_H__
#define __MESH_H__


#include <glew.h>
#include <glm.hpp>
#include <cstdint>


#define BUFFER_OFFSET(i) ((char *)nullptr + (i))


struct Vertex2D
{
	glm::vec3 position;
	glm::vec2 texCoords;
};


struct Vertex3D
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoordsAlpha;
};


struct Vertex3DBlendAnimation
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoordsAlpha;
};


class Mesh
{
public:
	//::.. CONSTRUCTORS ..:://
	Mesh();
	virtual ~Mesh();

	//::.. INITIALIZERS ..:://
	bool LoadMesh(Vertex2D * vertices, uint64_t numVerts);
	bool LoadMesh(Vertex3D * vertices, uint64_t numVerts);
	bool LoadMesh(Vertex3DBlendAnimation * vertices, uint64_t numVerts);
	bool FreeMesh();

	//::.. RENDER ..:://
	bool Render();

	//::.. GET FUNCTIONS ..:://
	bool GetIsLoaded();

	//::.. SET FUNCTIONS ..:://


	void Update();

private:
	bool		m_isLoaded;
	uint64_t	m_drawCount;
	GLuint		m_vao;
	GLuint		m_buffer;

	Vertex3D *	m_vertices;



};


#endif