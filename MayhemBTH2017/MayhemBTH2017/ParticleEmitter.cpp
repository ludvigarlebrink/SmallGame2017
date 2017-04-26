#include "ParticleEmitter.h"




ParticleEmitter::ParticleEmitter(ParticleSystem particleSystem)
{
	SetParticleSystem(particleSystem);

}
ParticleEmitter::ParticleEmitter() {

}


ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Emit() {
	

	m_particleSystem[1].UpdateParticles();
	m_particleSystem[1].RenderTransformed(1);


}

void ParticleEmitter::SetParticleSystem(ParticleSystem particleSystem) {

	for (int i = 0; i < m_nrof; i++)
		m_particleSystem[i] = particleSystem;
}