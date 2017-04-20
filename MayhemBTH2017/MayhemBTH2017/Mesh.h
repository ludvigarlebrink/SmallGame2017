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
	//fy fan..... det är ytterst pinsamt att det saknas grejer här.. 
	//Tangents och bitangents är viktiga bitar i varje program. 
	//Många implementationer kräver dessa två viktiga bitar av data.
	//Normalmap och massa andra implementationer kommer nu behöva räkna ut denna data på CPU'n
	//Om Bill Gates vore död skulle han vända sig i graven!
};

struct Vertex3DSkelAnimation
{
	glm::vec3	position;
	glm::vec3	normal;
	glm::vec3	texCoordsAlpha;
	glm::vec4	jointIDs;
	glm::vec4	weights;

};


class Mesh
{
public:
	//::.. CONSTRUCTORS ..:://
	Mesh();
	virtual ~Mesh();

	//::.. INITIALIZERS ..:://
	bool Load(Vertex2D * vertices, uint64_t numVerts);
	bool Load(Vertex3D * vertices, uint64_t numVerts);
	bool Load(Vertex3DSkelAnimation * vertices, uint64_t numVerts);
	bool Free();

	//::.. RENDER ..:://
	bool Render();

	//::.. GET FUNCTIONS ..:://
	bool GetIsLoaded();

	//::.. SET FUNCTIONS ..:://
	void SetRenderMode(GLenum renderMode);

	void Update();

private:
	bool		m_isLoaded;
	uint64_t	m_drawCount;
	GLuint		m_vao;
	GLuint		m_buffer;

	Vertex2D *				m_vertices2D;
	Vertex3D *				m_vertices3D;
	Vertex3DSkelAnimation *	m_vertices3DSkelAnimation;

	GLenum		m_renderMode;

};


#endif