#ifndef __SHADERPROG_H__
#define __SHADERPROG_H__

#include "Shader.h"

class ShaderProg
{
public:
	//::.. CONSTRUCTORS ..:://
	ShaderProg();
	virtual ~ShaderProg();

	void SetShaders(const Shader* shader1, uint32_t numShader);
	void InitShaders();
	void Bind();
	void Update();
	void UpdateAnim();

private:



	Shader* m_vert, m_geom, m_frag;

	uint32_t m_numShader;
	uint32_t m_numUniforms;

};

#endif // ! __SHADERPROG_H__