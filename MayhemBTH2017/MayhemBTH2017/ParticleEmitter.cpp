#include "ParticleEmitter.h"




ParticleEmitter::ParticleEmitter()
{

	m_particleSystem = nullptr;

}


ParticleEmitter::~ParticleEmitter()
{
	Delete();
}

void ParticleEmitter::Render() {

	if (m_render)
		m_particleSystem->RenderTransformed();

}

void ParticleEmitter::Update() {

	if (m_timer >= 0 && m_timer <= 5)
		m_timer += TimeManager::GetDeltaTime();

	if (m_render)
		m_particleSystem->UpdateParticles();

	if (m_timer >= 5) {
		Delete();
		m_timer = -1;
	}

}

void ParticleEmitter::Refresh(glm::vec3 position) {


}

void ParticleEmitter::Delete() {

	std::cout << "Particle Emitt Delete" << std::endl;

	m_render = false;
	if (m_particleSystem != nullptr)
	{
		delete m_particleSystem;
		m_particleSystem = nullptr;

	}


}

void ParticleEmitter::SetParticleSystem(std::string shadername, glm::vec3 pos, glm::vec4 col, GLfloat size, int nrOf, float life) {

	if (m_particleSystem == nullptr)
	{
		m_timer = 0;
		m_render = true;

		m_particleSystem = new ParticleSystem(shadername, pos, col, size, nrOf, life);
	}
}