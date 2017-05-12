#include "ParticleEmitter.h"




ParticleEmitter::ParticleEmitter()
{
	std::cout<< "Constructor Particle Emitter" << std::endl;
	m_particleSystem = nullptr;
	m_timer = 0;

}


ParticleEmitter::~ParticleEmitter()
{
	Delete();
}

void ParticleEmitter::Render() {

	if (m_particleSystem != nullptr) {
		m_particleSystem->UpdateParticles();
		m_particleSystem->RenderTransformed();
	}
}

void ParticleEmitter::Update() {

	if (m_timer >=0)
		m_timer += TimeManager::GetDeltaTime();



	if (m_timer >= 2) {
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

	std::cout << "set particle system in Emitter:" << std::endl;

	if (m_particleSystem == nullptr)
	{

		m_render = true;
		m_timer = 0;

		m_particleSystem = new ParticleSystem(shadername, pos, col, size, nrOf, life);
		std::cout << "New System: Particle Emitter" << std::endl;
	}
}