#include "ParticleTransform.h"



ParticleTransform::ParticleTransform()
{
	
}


ParticleTransform::~ParticleTransform()
{
}

void ParticleTransform::AddAttributeLocation() {

	std::cout << "ParticleTransform"<<std::endl;
	Particle p[6];
	m_drawCount = 6;
	p[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
	p[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
	p[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	p[3].position = glm::vec3(0.5f, -0.5f, 0.0f);
	p[4].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	p[5].position = glm::vec3(-0.5f, -0.5f, 0.0f);

	Transform temp;
	temp.SetPosition(2, 2, 10);
	tmpTransform = temp;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * m_drawCount, p, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	uint64_t offset = 0;
	// Position.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(offset));
	// Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(offset + 3));
	// Velocity
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(offset + 6));
	// Time alive
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(offset + 7));
	// Unbind
	glBindVertexArray(0);


}

GLuint ParticleTransform::GetVAO() {
	return this->m_vao;
}
GLuint ParticleTransform::GetDrawCount(){
	return this->m_buffer;
}


