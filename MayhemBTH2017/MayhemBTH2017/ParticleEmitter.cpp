#include "ParticleEmitter.h"

#ifdef _DEBUG
#define DEBUG_NEW_PLACEMENT (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW_PLACEMENT
#endif

int* a = new DEBUG_NEW_PLACEMENT int(5);
#include <stdlib.h>  
#include <crtdbg.h>  




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

			m_particleSystem.at(i)->RenderTransformed(transform);
		}
	}
}

void ParticleEmitter::Update() {



	for (int i = 0; i < m_particleSystem.size(); i++) {

		m_particleSystem.at(i)->UpdateParticles();


		//After 0.5 seconds delete particles

		if (m_particleSystem.at(i)->GetTimer() > 0.5f) {

			//Delete the Particle System at position i 
			delete m_particleSystem.at(i);

			m_particleSystem.erase(m_particleSystem.begin() + i);

			//Clear the vector


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
	m_particleSystem.clear();

}

void ParticleEmitter::SetParticleSystem(std::string shadername, glm::vec3 pos, glm::vec4 col, GLfloat size, int nrOf, float life) {


	m_particleSystem.push_back(new ParticleSystem(shadername, pos, col, size, nrOf, life));


}