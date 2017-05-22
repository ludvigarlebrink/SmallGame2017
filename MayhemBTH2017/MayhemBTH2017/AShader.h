#ifndef __ASHADER_H__
#define __ASHADER_H__


#include "Transform.h"
#include "Camera.h"
#include <Windows.h>
#include <glew.h>
#include<GL\GLU.h>
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
	AShader(const std::string& filename, bool hasGeomShader, bool particles);
	virtual ~AShader();															//Destructor

	//::.. GET FUNCTIONS ..:://
	GLuint GetProgramID();
	GLuint GetTextureID();

	//::.. MODIFY FUNCTIONS ..:://
	void Init(const std::string& filename, bool hasGeomShader, bool particles);
	void Release(int nr);
	void Bind();
	virtual void Update(Transform& transform, Camera& camera);
	void SendTexture(GLuint id, const GLchar* name, glm::vec4 UV);

	//::.. PROTECTED FUNCTIONS ..:://
	virtual void AddAttributeLocation();
	virtual void AddUniforms();
	void TempUpdateAlpha(GLfloat a);

private:
	//::.. HELP FUNCTIONS ..:://
	static GLuint CreateShader(const std::string& textfile, GLenum shaderType);
	static std::string LoadShader(const std::string& filename);
	static void Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);

private:
	enum Shader
	{
		VERTEX_SHADER = 0,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		NR_SHADERS
	};

	enum Uniforms
	{
		M,
		V,
		P,
		ALPHA,
		DIFFUSE_MAP,
		NR_UNIFORMS
	};

	bool m_hasGeomShader;

	GLuint m_programID;
	GLuint m_shader[NR_SHADERS];
	GLuint m_uniforms[NR_UNIFORMS];
	GLuint m_textureID;
};

#endif

