#include "ToonShader.h"

//::.. CONSTRUCTORS ..:://

ToonShader::ToonShader()
{
}


ToonShader::~ToonShader()
{
}


//::.. HELP FUNCTIONS ..:://

void ToonShader::UpdateTextures()
{
	glUseProgram(this->GetProgramID());

	//glUniform1i(glGetUniformLocation(this->GetProgramID(),
	//	"test"),0);
	glUniform1i(glGetUniformLocation(this->GetProgramID(),
		"t"), 1);
	/*glUniform1i(glGetUniformLocation(this->GetProgramID(),
		"tx"), 2);
	glUniform1i(glGetUniformLocation(this->GetProgramID(),
		"ty"), 3);*/
	//TBA
}

void ToonShader::UpdateUniforms(Transform& transform, Camera& camera)
{
	glUseProgram(this->GetProgramID());
	this->Update(transform, camera);
	this->AddUniforms();
	
	
	GLuint U_loc = glGetUniformLocation(this->GetProgramID(), "Color");

	glUniform3f(U_loc, 1, 0.5, 1);

	//TBA
}
