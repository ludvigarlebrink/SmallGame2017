#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include "Camera.h"
#include "ParticleSystem.h"

class ParticleEmitter
{
public:
	ParticleEmitter();


	virtual ~ParticleEmitter();
	void Render(Transform transform);
	void Update();

	void Delete();
	void SetParticleSystem(std::string shadername, glm::vec3 pos, glm::vec4 col, GLfloat size, const int nrOf, float life);
	void Refresh(glm::vec3 position);
private:
	GLfloat					m_timer = 0;
	const static int		m_nrof = 10;

	std::vector<ParticleSystem*>	m_particleSystem;
	Camera					m_camera;
	std::string				m_shaderName;
	glm::vec3				m_pos;
	glm::vec4				m_col;
	float					m_size;
	bool					m_render;
	int						m_nrOf;
	float					m_life;



};

#endif 
