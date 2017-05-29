#include "QuadShader.h"


//::..CONSTRUCTORS..:://
QuadShader::QuadShader()
{
}

QuadShader::QuadShader(const std::string& filename, bool hasGeomShader)
{
	Init(filename, hasGeomShader);
	m_effects = PostProcessingManager::Get();

}

QuadShader:: ~QuadShader()
{
	Release();
}

//::..GET FUNCTIONS..:://
GLuint QuadShader::GetProgramID()
{
	return m_programID;
}

//::..HELPER FUNCTIONS..:://
void QuadShader::Init(const std::string& filename, bool hasGeomShader)
{
	m_programID = glCreateProgram();

	m_hasGeomShader = false;

	// Create shaders.
	m_shader[VERTEX_SHADER] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER);
	m_shader[FRAGMENT_SHADER] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);

	glAttachShader(m_programID, m_shader[VERTEX_SHADER]);
	glAttachShader(m_programID, m_shader[FRAGMENT_SHADER]);

	AddAttributeLocation();

	glLinkProgram(m_programID);
	glValidateProgram(m_programID);

	AddUniforms();
}


void QuadShader::Release()
{
	// OBS DOESNT WORK YET
	for (unsigned int i = 0; i < NR_SHADERS; i++) {
		glDetachShader(m_programID, m_shader[i]);
		glDeleteShader(m_shader[i]);
	}

	glDeleteProgram(m_programID);
}


void QuadShader::Bind()
{
	glUseProgram(m_programID);
}

void QuadShader::Update(Transform& transform, Camera& camera)
{
	glUniformMatrix4fv(m_uniforms[M], 1, GL_FALSE, &transform.GetModelMatrix()[0][0]);
	glUniformMatrix4fv(m_uniforms[V], 1, GL_FALSE, &camera.GetView()[0][0]);
	glUniformMatrix4fv(m_uniforms[P], 1, GL_FALSE, &camera.GetProjection()[0][0]);

	glUniform1i(m_uniforms[DIFFUSE_MAP], 1);
}

void QuadShader::UpdateBool()
{


	glUniform1i(glGetUniformLocation(m_programID, "Shake"), PostProcessingManager::IsShaking());
	glUniform1i(glGetUniformLocation(m_programID, "Chaos"), PostProcessingManager::IsChaos());
	glUniform1i(glGetUniformLocation(m_programID, "Atomic"), PostProcessingManager::IsAtomic());
	
	glUniform1f(glGetUniformLocation(m_programID, "STime"), PostProcessingManager::GetShakingTime());
	glUniform1f(glGetUniformLocation(m_programID, "CTime"), PostProcessingManager::GetChaosTime());
	glUniform1f(glGetUniformLocation(m_programID, "ATime"), PostProcessingManager::GetAtmoicTime());




}

void QuadShader::AddAttributeLocation()
{
	// These are three attributes are set for all shaders.
	glBindAttribLocation(m_programID, 0, "Position");
	glBindAttribLocation(m_programID, 1, "TexCoords");
}

void QuadShader::AddUniforms()
{
	m_uniforms[M] = glGetUniformLocation(m_programID, "M");
	m_uniforms[V] = glGetUniformLocation(m_programID, "V");
	m_uniforms[P] = glGetUniformLocation(m_programID, "P");
	m_uniforms[DIFFUSE_MAP] = glGetUniformLocation(m_programID, "DiffuseMap");
}




GLuint QuadShader::CreateShader(const std::string& textfile, GLenum shaderType)
{

	GLuint shader = glCreateShader(shaderType);

	const GLchar* shaderSource[1];
	GLint sourceLength[1];

	shaderSource[0] = textfile.c_str();
	sourceLength[0] = textfile.length();

	glShaderSource(shader, 1, shaderSource, sourceLength);
	glCompileShader(shader);

	return shader;
}

std::string QuadShader::LoadShader(const std::string& filename)
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