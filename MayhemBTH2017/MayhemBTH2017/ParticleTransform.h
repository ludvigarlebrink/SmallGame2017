#ifndef __PARTICLETRANSFORM_H__
#define __PARTICLETRANSFORM_H__
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

#include "AShader.h"
#include "Particle.h"




class ParticleTransform:public AShader
{
public:

	ParticleTransform();
	virtual ~ParticleTransform();
	void AddAttributeLocation();
	GLuint GetVAO();
	GLuint GetDrawCount();

private:
private:
	GLuint m_drawCount;
	Transform tmpTransform;
	GLuint m_vao;
	GLuint m_buffer;
};

#endif