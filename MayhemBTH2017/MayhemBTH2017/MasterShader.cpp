#include "MasterShader.h"

//::..CONSTRUCTORS..:://
AShader::AShader(const std::string& filename)
	: m_programID(glCreateProgram())
{
	Init(filename);

}

//Destructor
AShader:: ~AShader() {

	Release();
}

//::..GET FUNCTIONS..:://
GLuint AShader::GetProgramID() {
	return m_programID;
}

//::..HELPER FUNCTIONS..:://
void AShader::Init(const std::string& filename) {
	//create shader
	m_shader[0] = CreateShader(LoadShader(filename + ".vert"), GL_VERTEX_SHADER); //text of shader, shader type (vs)
	m_shader[1] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);
	m_shader[2] = CreateShader(LoadShader(filename + ".geo"), GL_GEOMETRY_SHADER);

	//add every shader to our shader program
	for (GLuint i = 0; i < NR_SHADERS; i++) {
		glAttachShader(m_programID, m_shader[i]); //add the shader of myShaders[i] to our shader program myProgram
		Debug(m_shader[i], GL_COMPILE_STATUS, false, "Error: Shader attachment failed.");
	}

	//These are three attributes are set for all shaders
	glBindAttribLocation(m_programID, 0, "vertex_position"); //program which the association is made, index of vertex, name bound to vertex shader attribute index
	glBindAttribLocation(m_programID, 1, "vertex_color"); //these are non-uniform, in comparision with glGetUniformLocation which are uniform
	glBindAttribLocation(m_programID, 2, "uv_coordinates");

	//Custom attributes for children of MasterShader
	AddAttributeLocation();

	glLinkProgram(m_programID);

	Debug(m_programID, GL_LINK_STATUS, true, "Error: Linking failed: ");
	glValidateProgram(m_programID);
	Debug(m_programID, GL_VALIDATE_STATUS, true, "Error: Invalid program: ");
}

void AShader::Release() {
	for (unsigned int i = 0; i < NR_SHADERS; i++) {
		glDetachShader(m_programID, m_shader[i]);
		glDeleteShader(m_shader[i]);
	}

	glDeleteProgram(m_programID);
}
void AShader::Bind() {
	glUseProgram(m_programID);
}
GLuint AShader::CreateShader(const std::string& textfile, GLenum shaderType) {

	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
		std::cout << "Error while creating shader" << std::endl;

	const GLchar* shaderSource[1];
	GLint sourceLenght[1];

	shaderSource[0] = textfile.c_str();
	sourceLenght[0] = textfile.length();

	glShaderSource(shader, 1, shaderSource, sourceLenght);
	glCompileShader(shader);
	Debug(shader, GL_COMPILE_STATUS, false, "Compilation failed\n");
	glValidateProgram(shader);
	return shader;
}
std::string AShader::LoadShader(const std::string& filename) {

	std::string line;
	std::ifstream readFile(filename); // read the file
	std::string tempFile;
	while (std::getline(readFile, line)) {
		tempFile += line;
		tempFile.push_back('\n');
	}

	return tempFile;
}
void AShader::Debug(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg) {

	GLint errorCheck = 0;
	GLchar logLenght[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &errorCheck);
	else
		glGetShaderiv(shader, flag, &errorCheck);

	if (errorCheck == GL_FALSE) {

		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(logLenght), 0, logLenght);
		else
			glGetShaderInfoLog(shader, sizeof(logLenght), 0, logLenght);
		std::cout << errorMsg << ": '" << logLenght << "'" << std::endl;
	}
}