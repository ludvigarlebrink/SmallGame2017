#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(std::string shadername, glm::vec3 pos, glm::vec4 col, GLfloat size, static const int nrOf, GLfloat lifetime)

{
	m_drawShader.Init(".\\Assets\\GLSL\\DrawShader", 1, 0); //Shade for drawing the transformed particles

	m_lifetime = lifetime;
	m_shaderName = shadername.c_str();
	//vertex shader program only

	m_pShader.Init(shadername, false, 1); //sets varying to "outValue" and only uses a vertex shader
	glLinkProgram(m_pShader.GetProgramID()); ///////////////////////////////////////////////LINK THE PROGRAM
	glUseProgram(m_pShader.GetProgramID());

	//GENERATE VERTEX ARRAY OBJECT
	glGenVertexArrays(1, &m_vao[0]); //Vertex array object to store  the data
	glBindVertexArray(m_vao[0]); //use this vertex arrray object

	PARTICLE_COUNT = nrOf;


	//for nr of particles in parameter, fill with info

	for (uint32_t i = 0; i < nrOf; i++) {

		m_particle[i].position = pos;
		m_particle[i].direction = (GetRandomDir());
		m_particle[i].color = col;
		m_particle[i].life = 0.0f;
		m_particle[i].size = size;


	}



	//BUFFERS
	glGenBuffers(1, &m_particleBufferA);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBufferA);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*PARTICLE_COUNT, m_particle, GL_STREAM_DRAW);


	//SET ATTRIBUTE POINTERS
	inPosID = glGetAttribLocation(m_pShader.GetProgramID(), "inPos");
	glEnableVertexAttribArray(inPosID);
	glVertexAttribPointer(inPosID, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(0));


	inDirID = glGetAttribLocation(m_pShader.GetProgramID(), "inDir");
	glEnableVertexAttribArray(inDirID);
	glVertexAttribPointer(inDirID, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3)));


	inColID = glGetAttribLocation(m_pShader.GetProgramID(), "inCol");
	glEnableVertexAttribArray(inColID);
	glVertexAttribPointer(inColID, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2));


	inTimeID = glGetAttribLocation(m_pShader.GetProgramID(), "inLife");
	glEnableVertexAttribArray(inTimeID);
	glVertexAttribPointer(inTimeID, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2 + sizeof(glm::vec4)));


	inSizeID = glGetAttribLocation(m_pShader.GetProgramID(), "inSize");
	glEnableVertexAttribArray(inSizeID);
	glVertexAttribPointer(inSizeID, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2 + sizeof(glm::vec4) + sizeof(GLfloat)));



	//Buffer to hold the outValue retrieved from the geopass vertex shader
	glGenBuffers(1, &m_particleBufferB);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBufferB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*PARTICLE_COUNT, 0, GL_STREAM_DRAW); //does not have any initial value (since its on the GPU)

	glEnable(GL_RASTERIZER_DISCARD); //Disable rasterizer
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBufferB);

	//defines bufferB as the current transform feedback buffer
	//BUFFER A->BUFFER B
	//SEND THE DATA TO BUFFER B
	//The output from geometrypass-vertexshader is catched by the transformBuffer!
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glEndTransformFeedback();
	glFlush();

	std::swap(m_particleBufferA, m_particleBufferB); //input in bufferB becomes input 

	glDisable(GL_RASTERIZER_DISCARD);
	glBindVertexArray(0);


	//// INFO FOR TRIANGLE

	Transform tpm;
	tpm.SetPosition(0, 0, 100);
	tmpTransform = tpm;
	m_timerCounter += 0.4f;
}

ParticleSystem::ParticleSystem() {}
glm::vec3 ParticleSystem::GetRandomDir() {

	return glm::vec3((rand() % (0, 1000 + 1000)) - 1000, (rand() % (0, 1000 + 1000)) - 1000, (rand() % (0, 1000 + 1000)) - 1000);
}


ParticleSystem::~ParticleSystem()
{





	glDeleteProgram(m_pShader.GetProgramID());
	glDeleteProgram(m_drawShader.GetProgramID());

}

void ParticleSystem::AddAttributeLocation() {





}


void ParticleSystem::AddTimerUniform() {

	this->AddUniforms();

}

void ParticleSystem::TransformFeedbackSwap() {



}

void ParticleSystem::LoadParticleVBOS(Particle* p, GLuint nrOfVerts) {


}

void ParticleSystem::RenderTransformed(GLuint textureID) {

	m_drawShader.Bind();
	m_camera.SetRotation(0.0f, 0.0f);
	m_camera.SetPosition(glm::vec3(((48 / 2) - 0.5f), ((54 / 2) + 0.5f), -60));
	m_drawShader.Update(tmpTransform, m_camera);

	glBindVertexArray(m_drawVAO);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glBindVertexArray(0);

}

void ParticleSystem::Emitt() {

	//if (m_timerCounter >= m_lifetime) {
	//	m_timerCounter = 0;
	//
	//	m_drawShader.Init(".\\Assets\\GLSL\\DrawShader", 1, 0); //Shade for drawing the transformed particles


	//	//vertex shader program only
	//	m_pShader.Init(m_shaderName, false, 1); //sets varying to "outValue" and only uses a vertex shader
	//	glLinkProgram(m_pShader.GetProgramID()); ///////////////////////////////////////////////LINK THE PROGRAM
	//	glUseProgram(m_pShader.GetProgramID());

	//	//GENERATE VERTEX ARRAY OBJECT
	//	glGenVertexArrays(1, &m_vao[0]); //Vertex array object to store  the data
	//	glBindVertexArray(m_vao[0]); //use this vertex arrray object



	//	//for nr of particles in parameter, fill with info
	//	PARTICLE_COUNT;
	//	for (uint32_t i = 0; i < PARTICLE_COUNT; i++) {

	//		m_particle[i].direction = (GetRandomDir());
	//	


	//	}


	//	//BUFFERS
	//	glGenBuffers(1, &m_particleBufferA);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_particleBufferA);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*PARTICLE_COUNT, m_particle, GL_STREAM_DRAW);


	//	//SET ATTRIBUTE POINTERS
	//	inPosID = glGetAttribLocation(m_pShader.GetProgramID(), "inPos");
	//	glEnableVertexAttribArray(inPosID);
	//	glVertexAttribPointer(inPosID, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(0));


	//	inDirID = glGetAttribLocation(m_pShader.GetProgramID(), "inDir");
	//	glEnableVertexAttribArray(inDirID);
	//	glVertexAttribPointer(inDirID, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3)));


	//	inColID = glGetAttribLocation(m_pShader.GetProgramID(), "inCol");
	//	glEnableVertexAttribArray(inColID);
	//	glVertexAttribPointer(inColID, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2));


	//	inTimeID = glGetAttribLocation(m_pShader.GetProgramID(), "inLife");
	//	glEnableVertexAttribArray(inTimeID);
	//	glVertexAttribPointer(inTimeID, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2 + sizeof(glm::vec4)));


	//	inSizeID = glGetAttribLocation(m_pShader.GetProgramID(), "inSize");
	//	glEnableVertexAttribArray(inSizeID);
	//	glVertexAttribPointer(inSizeID, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2 + sizeof(glm::vec4) + sizeof(GLfloat)));



	//	//Buffer to hold the outValue retrieved from the geopass vertex shader
	//	glGenBuffers(1, &m_particleBufferB);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_particleBufferB);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*PARTICLE_COUNT, 0, GL_STREAM_DRAW); //does not have any initial value (since its on the GPU)

	//	glEnable(GL_RASTERIZER_DISCARD); //Disable rasterizer
	//	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBufferB);

	//	//defines bufferB as the current transform feedback buffer
	//	//BUFFER A->BUFFER B
	//	//SEND THE DATA TO BUFFER B
	//	//The output from geometrypass-vertexshader is catched by the transformBuffer!
	//	glBeginTransformFeedback(GL_POINTS);
	//	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	//	glEndTransformFeedback();
	//	glFlush();

	//	std::swap(m_particleBufferA, m_particleBufferB); //input in bufferB becomes input 

	//	glDisable(GL_RASTERIZER_DISCARD);
	//	glBindVertexArray(0);


	//	//// INFO FOR TRIANGLE

	//	Transform tpm;
	//	tpm.SetPosition(0, 0, 100);
	//	tmpTransform = tpm;
	//	m_timerCounter += 0.4f;
	//}
}
void ParticleSystem::UpdateParticles() {


	glUseProgram(m_pShader.GetProgramID());
	glEnable(GL_RASTERIZER_DISCARD);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleBufferA);


	//SET ATTRIBUTE POINTERS
	inPosID = glGetAttribLocation(m_pShader.GetProgramID(), "inPos");
	glEnableVertexAttribArray(inPosID);
	glVertexAttribPointer(inPosID, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(0));


	inDirID = glGetAttribLocation(m_pShader.GetProgramID(), "inDir");
	glEnableVertexAttribArray(inDirID);
	glVertexAttribPointer(inDirID, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3)));


	inColID = glGetAttribLocation(m_pShader.GetProgramID(), "inCol");
	glEnableVertexAttribArray(inColID);
	glVertexAttribPointer(inColID, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2));


	inTimeID = glGetAttribLocation(m_pShader.GetProgramID(), "inLife");
	glEnableVertexAttribArray(inTimeID);
	glVertexAttribPointer(inTimeID, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2 + sizeof(glm::vec4)));


	inSizeID = glGetAttribLocation(m_pShader.GetProgramID(), "inSize");
	glEnableVertexAttribArray(inSizeID);
	glVertexAttribPointer(inSizeID, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(glm::vec3) * 2 + sizeof(glm::vec4) + sizeof(GLfloat)));

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBufferB);
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glEndTransformFeedback();
	std::swap(m_particleBufferA, m_particleBufferB);
	glDisable(GL_RASTERIZER_DISCARD);

	//glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(info), &info);
	//std::cout << info[0] << ". " << info[1] << ", " << info[2] << ", " << info[3] << ", " << info[4] << ", " << info[5] << std::endl;


	//m_timerCounter += 0.02f;


	//if (m_timerCounter >= m_lifetime) {
	//	//this->Release();
	//	//m_drawShader.Release();
	//	m_timerCounter == 0;
	//}



	//Clear depth buffer for the particles
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



}

