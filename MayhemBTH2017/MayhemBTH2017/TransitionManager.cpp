#include "TransitionManager.h"


TransitionManager * TransitionManager::m_instance = nullptr;

GLuint TransitionManager::m_shader = 0;
GLuint TransitionManager::m_vao = 0;
GLuint TransitionManager::m_buffer = 0;
GLuint TransitionManager::m_uniforms[] = { 0 };

GLfloat TransitionManager::m_t = 1.2f;

bool TransitionManager::m_isFadingIn = false;
bool TransitionManager::m_isFadingOut = false;
bool TransitionManager::m_isBlack = false;


TransitionManager::TransitionManager()
{
}


TransitionManager::~TransitionManager()
{
}


void TransitionManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		Init();
	}
}


void TransitionManager::ShutDown()
{

}


void TransitionManager::Update()
{
	if (!m_isBlack && !m_isFadingIn && !m_isFadingOut)
	{
		return;
	}

	if (m_isFadingIn)
	{
		m_t += TimeManager::GetDeltaTime() * 0.6f;
		if (m_t > 1.2f)
		{
			m_isFadingIn = false;
			m_isFadingOut = false;
			m_isBlack = false;
			m_t = 1.2f;
		}
	}
	else if (m_isFadingOut)
	{
		m_t -= TimeManager::GetDeltaTime() * 1.8f;
		if (m_t < 0.0f)
		{
			m_isFadingIn = false;
			m_isFadingOut = false;
			m_isBlack = true;
			m_t = 0.0f;
		}
	}
	else
	{
		m_t = 0.0f;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_shader);

	glUniform1f(m_uniforms[T], m_t);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glUseProgram(0);

	glDisable(GL_BLEND);
}



bool TransitionManager::GetIsFadingIn()
{
	return m_isFadingIn;
}


bool TransitionManager::GetIsFadingOut()
{
	return m_isFadingOut;
}


bool TransitionManager::GetIsBlack()
{
	return m_isBlack;
}



void TransitionManager::StartFadingOut()
{
	m_isFadingIn = false;
	m_isFadingOut = true;
	m_isBlack = false;
}


void TransitionManager::StartFadingIn()
{
	m_isFadingIn = true;
	m_isFadingOut = false;
	m_isBlack = false;
}

//::.. HELP FUNCTIONS ..:://
void TransitionManager::Init()
{

	std::string shaders[2];
	shaders[0] = ".\\Assets\\GLSL\\TransitionShader.vert";
	shaders[1] = ".\\Assets\\GLSL\\TransitionShader.frag";

	uint32_t shaderTypes[2];
	shaderTypes[0] = ShaderManager::VERT_SHADER;
	shaderTypes[1] = ShaderManager::FRAG_SHADER;


	m_shader = ShaderManager::CreateAndAttachShaders("Transition", shaders, shaderTypes, 2);

	glBindAttribLocation(m_shader, 0, "Position");

	ShaderManager::LinkAndValidate("Transition");

	m_uniforms[T] = glGetUniformLocation(m_shader, "T");

	glm::vec3 vertices[6] =
	{
		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f)
	};

	// Generate VAO.
	glGenVertexArrays(1, &m_vao);

	// Bind VAO.
	glBindVertexArray(m_vao);

	// Enable attributes.
	glEnableVertexAttribArray(0);

	// Generate buffers.
	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

	// Copy data to the gpu.
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 6, vertices, GL_STATIC_DRAW);

	uint64_t offset = 0;

	// Position.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);


	// Unbind
	glBindVertexArray(0);
}