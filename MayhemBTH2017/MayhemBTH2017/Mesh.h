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
	//fy fan..... det �r ytterst pinsamt att det saknas grejer h�r.. 
	//Tangents och bitangents �r viktiga bitar i varje program. 
	//M�nga implementationer kr�ver dessa tv� viktiga bitar av data.
	//Normalmap och massa andra implementationer kommer nu beh�va r�kna ut denna data p� CPU'n
	//Om Bill Gates vore d�d skulle han v�nda sig i graven!
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