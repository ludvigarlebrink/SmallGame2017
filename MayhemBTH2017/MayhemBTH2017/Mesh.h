#ifndef __MESH_H__
#define __MESH_H__


#include <glew.h>
#include <glm.hpp>
#include <cstdint>


#define BUFFER_OFFSET(i) ((char *)nullptr + (i))


struct Vertex
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
	bool LoadMesh(Vertex* vertices, uint64_t numVerts);
	bool FreeMesh();
	bool LoadQuad();

	//::.. RENDER ..:://
	bool Render();
	bool RenderQuad();

	//::.. GET FUNCTIONS ..:://
	bool GetIsLoaded();

	void Update();

private:
	bool		m_isLoaded;
	uint64_t	m_drawCount;
	GLuint		m_vao;
	GLuint		m_buffer;
	Vertex *	m_vertices;

	GLuint m_quadVAO;
	GLuint m_quadVBO;
};


#endif