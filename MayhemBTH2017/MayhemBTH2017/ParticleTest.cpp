#include "ParticleTest.h"



ParticleTest::ParticleTest()
{
	ParticleSystem particles(".\\Assets\\GLSL\\GeometryPass", glm::vec3(40, 20, 0), glm::vec4(1.0, 0.0, 1.0, 1.0), 10.0f, 5005.0f, 4.0f);
	m_particles = particles;
	//drawShader.Init(".\\Assets\\GLSL\\DrawShader", 1, 0);
}

void ParticleTest::Render()
{
	// << "render" << std::endl;
	//Camera camera;
	//camera.SetPosition(glm::vec3(0, 2, -0));
	//Transform transform;


}


ParticleTest::~ParticleTest()
{
}
