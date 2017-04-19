#ifndef __SHADERPROG_H__
#define __SHADERPROG_H__

#include "Shader.h"

class ShaderProg
{
public:


	ShaderProg();
	virtual ~ShaderProg();

	void SetShaders(const Shader* vert, const Shader* geom, const Shader* frag);
	void InitShaders();
	void Bind();
	void Update();

private:
	enum ShaderTypes
	{
		VERT = 1,
		GEOM = 2,
		FRAG = 4
	};

	Shader* m_vert, m_geom, m_frag;

	uint32_t m_numShader;
	uint32_t m_shaderProfile;

};

#endif // ! __SHADERPROG_H__