#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

//#include "MemoryManager.h"
//#include "StackAllocator.h"

#include <glew.h>
#include <SDL.h>
#include <glm.hpp>
#include <iostream>
#include <fstream>
#include <string>

class AShader {
public:
	//::..CONSTRUCTORS..:://
	AShader(const std::string& filename);

	//Destructor
	virtual ~AShader();

	//::..GET FUNCTIONS..:://
	GLuint GetProgramID();

	//::..HELPER FUNCTIONS..:://
	void Init(const std::string& filename);
	void Release();
	void virtual Update() = 0;
	void Bind();

private:
	//::..HELPER FUNCTIONS..:://
	static GLuint CreateShader(const std::string& textfile, GLenum shaderType);
	static std::string LoadShader(const std::string& filename);
	static void Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);
	void virtual AddAttributeLocation() = 0;
private:
	const static GLuint NR_SHADERS = 3;
	GLuint m_programID;
	GLuint m_shader[NR_SHADERS];

};

#endif

