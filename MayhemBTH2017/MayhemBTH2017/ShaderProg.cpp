#include "ShaderProg.h"



ShaderProg::ShaderProg()
{
	m_numShader = 0;
	m_shaderProfile = 0;
}


ShaderProg::~ShaderProg()
{

}

void ShaderProg::SetShaders(const Shader * vert, const Shader * geom, const Shader * frag)
{

	if (vert != nullptr)
	{
		m_shaderProfile += VERT;
		++m_numShader;
	}

	if (geom != nullptr)
	{
		m_shaderProfile += GEOM;
		++m_numShader;
	}

	if (frag != nullptr)
	{
		m_shaderProfile += FRAG;
		++m_numShader;
	}

}

void ShaderProg::Bind()
{
	
}

void ShaderProg::Update()
{

}
