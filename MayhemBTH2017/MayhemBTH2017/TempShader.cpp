#include "TempShader.h"



//::..CONSTRUCTORS..:://
TempShader::TempShader()
{
}

TempShader::TempShader(const std::string& filename, bool hasGeomShader)
{
	Init(filename, hasGeomShader);
}

TempShader:: ~TempShader()
{
	Release();
}

//::..GET FUNCTIONS..:://
GLuint TempShader::GetProgramID()
{
	return m_programID;
}

//::..HELPER FUNCTIONS..:://
void TempShader::Init(const std::string& filename, bool hasGeomShader)
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


void TempShader::Release()
{
	// OBS DOESNT WORK YET
	for (unsigned int i = 0; i < NR_SHADERS; i++) {
		glDetachShader(m_programID, m_shader[i]);
		glDeleteShader(m_shader[i]);
	}

	glDeleteProgram(m_programID);
}


void TempShader::Bind()
{
	glUseProgram(m_programID);
}

void TempShader::Update(Transform& transform, Camera& camera, JointSkeleton& skel)
{
	glUniformMatrix4fv(m_uniforms[M], 1, GL_FALSE, &transform.GetModelMatrix()[0][0]);
	glUniformMatrix4fv(m_uniforms[V], 1, GL_FALSE, &camera.GetView()[0][0]);
	glUniformMatrix4fv(m_uniforms[P], 1, GL_FALSE, &camera.GetProjection()[0][0]);

	glUniformMatrix4fv(m_uniforms[JOINTS], 4, GL_FALSE, &skel.GetMat()[0][0][0]);
}


void TempShader::AddAttributeLocation()
{
	// These are three attributes are set for all shaders.
	glBindAttribLocation(m_programID, 0, "Position");
	glBindAttribLocation(m_programID, 1, "Normal");
	glBindAttribLocation(m_programID, 2, "TexCoords");
	glBindAttribLocation(m_programID, 3, "JointIndex");
	glBindAttribLocation(m_programID, 4, "JointWeight");

}

void TempShader::AddUniforms()
{
	m_uniforms[M] = glGetUniformLocation(m_programID, "M");
	m_uniforms[V] = glGetUniformLocation(m_programID, "V");
	m_uniforms[P] = glGetUniformLocation(m_programID, "P");
	m_uniforms[JOINTS] = glGetUniformLocation(m_programID, "Joints");
}




GLuint TempShader::CreateShader(const std::string& textfile, GLenum shaderType)
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

std::string TempShader::LoadShader(const std::string& filename)
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

void TempShader::Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg)
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