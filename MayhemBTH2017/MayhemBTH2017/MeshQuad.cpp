#include "MeshQuad.h"


	//::.. CONSTRUCTORS ..:://
MeshQuad::MeshQuad()
{
	m_camera.SetRotation(0.0f, -0.0f);
	m_camera.SetPosition(glm::vec3(((SIZE_X / 2) - 0.5f), ((SIZE_Y / 2) + 0.5f), -60));
	LoadMesh();
	quadShader.Init("QuadShader", false);
}


MeshQuad::~MeshQuad()
{
}

//::.. INITIALIZERS ..:://

bool MeshQuad::LoadMesh()
{
	GLfloat QuadVerts[] =
	{
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVerts), &QuadVerts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);


	return true;

}


//::.. RENDER ..:://

bool MeshQuad::Render()
{
	
	glUseProgram(quadShader.GetProgramID());
	quadShader.Update(m_transform, m_camera);
	glBindVertexArray(m_vao);
	

	
	return true;
}

//::.. HELP FUNCTIONS ..:://


void MeshQuad::Draw()
{

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}