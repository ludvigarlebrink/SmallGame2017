#ifndef __MESH_H__
#define __MESH_H__


#include <glew.h>
#include <glm.hpp>
#include <cstdint>


#define BUFFER_OFFSET(i) ((char *)nullptr + (i))


struct Vertex2D
{
	glm::vec2 position;
	glm::vec2 texCoords;
};


struct Vertex3D
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoordsAlpha;
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

	void Update(Vertex3D * vertices3D);

private:
	bool		m_isLoaded;
	uint64_t	m_drawCount;
	GLuint		m_vao;
	GLuint		m_buffer;

	int			m_vertexType;

	GLenum					m_renderMode;

};


#endif