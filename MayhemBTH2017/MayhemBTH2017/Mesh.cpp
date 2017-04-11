#include "Mesh.h"


#include <iostream>

//::.. CONSTRUCTORS ..:://
Mesh::Mesh()
	: m_isLoaded(false), m_drawCount(0), m_renderMode(GL_TRIANGLES)
{

}

Mesh::~Mesh()
{
	Free();
}


//::.. INITIALIZERS ..:://
bool Mesh::Load(Vertex2D * vertices, uint64_t numVerts)
{
	if (m_isLoaded)
	{
		return false;
	}

	m_drawCount = numVerts;
	m_vertices2D = vertices;

	// Generate VAO.
	glGenVertexArrays(1, &m_vao);

	// Bind VAO.
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// Generate buffers.
	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

	// Copy data to the gpu.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * numVerts, vertices, GL_STATIC_DRAW);

	uint64_t offset = 0;

	// Position.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), BUFFER_OFFSET(offset));
	offset += sizeof(glm::vec3);

	// Texture Coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), BUFFER_OFFSET(offset));

	// Unbind
	glBindVertexArray(0);
}


bool Mesh::Load(Vertex3D * vertices, uint64_t numVerts)
{
	if (m_isLoaded)
	{
		return false;
	}

	m_drawCount = numVerts;
	m_vertices3D = vertices;

	// Generate VAO.
	glGenVertexArrays(1, &m_vao);

	// Bind VAO.
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// Generate buffers.
	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

	// Copy data to the gpu.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * numVerts, vertices, GL_STATIC_DRAW);

	uint64_t offset = 0;

	// Position.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(offset));
	offset += sizeof(glm::vec3);

	// Normal.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(offset));
	offset += sizeof(glm::vec3);

	// Texture Coordinates.
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(offset));

	// Unbind
	glBindVertexArray(0);


	m_isLoaded = true;
	return true;
}

bool Mesh::Load(Vertex3DSkelAnimation * vertices, uint64_t numVerts)
{
	if (m_isLoaded)
	{
		return false;
	}

	m_drawCount = numVerts;
	m_vertices3DSkelAnimation = vertices;

	// Generate VAO.
	glGenVertexArrays(1, &m_vao);

	// Bind VAO.
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	// Generate buffers.
	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

	// Copy data to the gpu.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3DSkelAnimation) * numVerts, vertices, GL_DYNAMIC_DRAW);

	uint64_t offset = 0;

	// Position.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSkelAnimation), BUFFER_OFFSET(offset));
	offset += sizeof(glm::vec3);

	// Normal.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSkelAnimation), BUFFER_OFFSET(offset));
	offset += sizeof(glm::vec3);

	// Texture Coordinates.
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSkelAnimation), BUFFER_OFFSET(offset));
	offset += sizeof(glm::vec3);

	// Texture Coordinates.
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSkelAnimation), BUFFER_OFFSET(offset));
	offset += sizeof(glm::vec4);

	// Texture Coordinates.
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSkelAnimation), BUFFER_OFFSET(offset));

	// Unbind
	glBindVertexArray(0);


	m_isLoaded = true;
	return true;
}

bool Mesh::Free()
{
	if (!m_isLoaded)
	{
		return false;
	}

	glDeleteVertexArrays(1, &m_vao);

	m_isLoaded = false;
	return true;
}


//::.. RENDER ..:://
bool Mesh::Render()
{
	glBindVertexArray(m_vao);
	glDrawArrays(m_renderMode, 0, m_drawCount);
	glBindVertexArray(0);
	return true;
}


//::.. GET FUNCTIONS ..:://
bool Mesh::GetIsLoaded()
{
	return m_isLoaded;
}


void Mesh::SetRenderMode(GLenum renderMode)
{
	m_renderMode = renderMode;
}

void Mesh::Update()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * m_drawCount, m_vertices3D, GL_STATIC_DRAW);
}