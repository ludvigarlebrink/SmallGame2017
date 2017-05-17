#include "ParticleEmitter.h"




ParticleEmitter::ParticleEmitter()
{
	for (int i = 0; i < m_particleSystem.size(); i++) {
		m_particleSystem.at(i) = nullptr;
	}

}


ParticleEmitter::~ParticleEmitter()
{
	Delete();

}

void ParticleEmitter::Render(Transform transform) {

	for (int i = 0; i < m_particleSystem.size(); i++) {

		if (m_particleSystem.at(i) != nullptr) {

		//	m_particleSystem.at(i)->RenderTransformed(transform);
		}
	}
}

void ParticleEmitter::Update() {

	for (int i = 0; i < m_particleSystem.size(); i++) {

		//m_particleSystem.at(i)->UpdateParticles();

		if (m_particleSystem.at(i)->GetTimer() > 2.5f) {

			delete[] m_particleSystem.at(i);
			m_particleSystem.clear();
		//	m_particleSystem.erase(m_particleSystem.at(i));
		}
	}
}

void ParticleEmitter::Refresh(glm::vec3 position) {


}

void ParticleEmitter::Delete() {



	//m_render = false;

	//if (m_particleSystem != nullptr)
	//{
	//	delete m_particleSystem;
	//	m_particleSystem = nullptr;

	//}


}

void ParticleEmitter::SetParticleSystem(std::string shadername, glm::vec3 pos, glm::vec4 col, GLfloat size, int nrOf, float life) {




	m_particleSystem.push_back(new ParticleSystem(shadername, pos, col, size, nrOf, life));


}