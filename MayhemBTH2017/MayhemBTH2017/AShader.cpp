#include "AShader.h"
#include "AShader.h"



//::..CONSTRUCTORS..:://
AShader::AShader()
{
}

AShader::AShader(const std::string& filename, bool hasGeomShader)
{
	Init(filename, hasGeomShader);
}

AShader:: ~AShader() 
{
	Release();
}

//::..GET FUNCTIONS..:://
GLuint AShader::GetProgramID() 
{
	return m_programID;
}

//::..HELPER FUNCTIONS..:://
void AShader::Init(const std::string& filename, bool hasGeomShader) 
{
	m_programID = glCreateProgram();

	m_hasGeomShader = false;

	// Create shaders.
	m_shader[VERTEX_SHADER] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER);
	m_shader[FRAGMENT_SHADER] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);

	glAttachShader(m_programID, m_shader[VERTEX_SHADER]);
	Debug(m_shader[VERTEX_SHADER], GL_COMPILE_STATUS, false, "Error: Shader attachment failed.");
	glAttachShader(m_programID, m_shader[FRAGMENT_SHADER]);
	Debug(m_shader[FRAGMENT_SHADER], GL_COMPILE_STATUS, false, "Error: Shader attachment failed.");

	AddAttributeLocation();

	glLinkProgram(m_programID);
	Debug(m_programID, GL_LINK_STATUS, true, "Error: Linking failed: ");

	glValidateProgram(m_programID);
	Debug(m_programID, GL_VALIDATE_STATUS, true, "Error: Invalid program: ");

	AddUniforms();
}


void AShader::Release() 
{
	// OBS DOESNT WORK YET
	for (unsigned int i = 0; i < NR_SHADERS; i++) {
		glDetachShader(m_programID, m_shader[i]);
		glDeleteShader(m_shader[i]);
	}

	glDeleteProgram(m_programID);
}


void AShader::Bind()
{
	glUseProgram(m_programID);
}

void AShader::Update(Transform& transform, Camera& camera)
{
	glUniformMatrix4fv(m_uniforms[M], 1, GL_FALSE, &transform.GetModelMatrix()[0][0]);
	glUniformMatrix4fv(m_uniforms[V], 1, GL_FALSE, &camera.GetView()[0][0]);
	glUniformMatrix4fv(m_uniforms[P], 1, GL_FALSE, &camera.GetProjection()[0][0]);
}

void AShader::AddAttributeLocation()
{
	// These are three attributes are set for all shaders.
	glBindAttribLocation(m_programID, 0, "Position");
	glBindAttribLocation(m_programID, 1, "Normal");
	glBindAttribLocation(m_programID, 2, "TexCoords");
}

void AShader::AddUniforms()
{
	m_uniforms[0] = glGetUniformLocation(m_programID, "M");
	m_uniforms[1] = glGetUniformLocation(m_programID, "V");
	m_uniforms[2] = glGetUniformLocation(m_programID, "P");
}


GLuint AShader::CreateShader(const std::string& textfile, GLenum shaderType) 
{

	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cout << "Error while creating shader" << std::endl;
	}

	const GLchar* shaderSource[1];
	GLint sourceLength[1];

	shaderSource[0] = textfile.c_str();
	sourceLength[0] = textfile.length();

	glShaderSource(shader, 1, shaderSource, sourceLength);
	glCompileShader(shader);
	Debug(shader, GL_COMPILE_STATUS, false, "Compilation failed\n");

	return shader;
}

std::string AShader::LoadShader(const std::string& filename) 
{
	std::ifstream in(filename.c_str());

	std::string output;
	std::string line;

	if (in.is_open())
	{
		while (in.good())
		{
			getline(in, line);
			output.append(line + '\n');
		}
	}

	return output;
}

void AShader::Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg) 
{

	GLint errorCheck = 0;
	GLchar logLength[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &errorCheck);
	}
	else
	{
		glGetShaderiv(shader, flag, &errorCheck);
	}

	if (errorCheck == GL_FALSE) 
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(logLength), 0, logLength);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(logLength), 0, logLength);
		}

		std::cout << errorMsg << ": '" << logLength << "'" << std::endl;
	}
}