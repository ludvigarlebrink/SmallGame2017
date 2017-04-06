#ifndef __SHADER_H__
#define __SHADER_H__


#include "Transform.h"
#include "Camera.h"


#include <glew.h>
#include <SDL.h>
#include <glm.hpp>
#include <iostream>
#include <fstream>
#include <string>


class AShader 
{
public:
	//::.. CONSTRUCTORS ..:://
	AShader();
	AShader(const std::string& filename, bool hasGeomShader);
	virtual ~AShader();											//Destructor

	//::.. GET FUNCTIONS ..:://
	GLuint GetProgramID();

	//::.. MODIFY FUNCTIONS ..:://
	void Init(const std::string& filename, bool hasGeomShader);
	void Release();
	void Bind();
	virtual void Update(Transform& transform, Camera& camera);


	//::.. PROTECTED FUNCTIONS ..:://
	virtual void AddAttributeLocation();
	virtual void AddUniforms();

private:
	//::.. HELP FUNCTIONS ..:://
	static GLuint CreateShader(const std::string& textfile, GLenum shaderType);
	static std::string LoadShader(const std::string& filename);
	static void Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);

private:
	enum Shader
	{
		VERTEX_SHADER = 0,
		FRAGMENT_SHADER,
		NR_SHADERS
	};

	enum Uniforms
	{
		M,
		V,
		P,
		DIFFUSE_MAP,
		NR_UNIFORMS
	};

	bool m_hasGeomShader;

	GLuint m_programID;
	GLuint m_shader[NR_SHADERS];
	GLuint m_uniforms[NR_UNIFORMS];
};

#endif

