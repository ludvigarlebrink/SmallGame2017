#include "AtomicBomb.h"


bool AtomicBomb::m_sequenceStarted = false;

AtomicBomb::AtomicBomb()
{
	m_soundManager = SoundManager::Get();
	m_bomber = PrefabManager::Instantiate("Bomber", nullptr, nullptr, 0, "Bomber");
	m_atomicBomb = PrefabManager::Instantiate("AtomicBomb", nullptr, nullptr, 0, "AtomicBomb");
	m_bomber->SetRotation(0.0f, 90.0f, 0.0f);
	m_atomicBomb->SetRotation(90.0f, 0.0f, 0.0f);
//	VideoManager->VM

	m_bomber->SetPosition(glm::vec3(100.0f, 38.0f, -10.0f));
	m_atomicBomb->SetPosition(glm::vec3(42.0f, 38.0f, -10.0f));
	m_currState = 0;
	m_sequenceStarted = false;
	m_shakeEffect = false;
	m_t = 0.0f;


	std::string shaders[2];
	shaders[0] = ".\\Assets\\GLSL\\ExplosionShader.vert";
	shaders[1] = ".\\Assets\\GLSL\\ExplosionShader.frag";

	uint32_t shaderTypes[2];
	shaderTypes[0] = ShaderManager::VERT_SHADER;
	shaderTypes[1] = ShaderManager::FRAG_SHADER;


	m_shader = ShaderManager::CreateAndAttachShaders("Transition", shaders, shaderTypes, 2);

	glBindAttribLocation(m_shader, 0, "Position");

	ShaderManager::LinkAndValidate("Transition");

	m_uniforms[SCREEN_WIDTH] = glGetUniformLocation(m_shader, "ScreenWidth");
	m_uniforms[SCREEN_HEIGHT] = glGetUniformLocation(m_shader, "ScreenHeight");
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


AtomicBomb::~AtomicBomb()
{
}




void AtomicBomb::StartBombSequence()
{
	m_sequenceStarted = true;
}


void AtomicBomb::Update(Camera &cam)
{
	if (!m_sequenceStarted)
	{
		return;
	}

	m_bomber->SetPosition(glm::vec3(m_bomber->GetPosition().x - (TimeManager::GetDeltaTime() * 35.0f), 38.0f, -10.0f));

	switch (m_currState)
	{
	case FLYING:
		m_bomber->SetPosition(glm::vec3(m_bomber->GetPosition().x - (TimeManager::GetDeltaTime() * 20.0f), 38.0f, -10.0f));
		m_bomber->Render(cam);

		if (m_bomber->GetPosition().x < 38)
		{
			m_currState = BOMB_DROPPED;
		}

		break;

	case BOMB_DROPPED:
		m_bomber->SetPosition(glm::vec3(m_bomber->GetPosition().x - (TimeManager::GetDeltaTime() * 20.0f), 38.0f, -10.0f));
		m_atomicBomb->SetPosition(glm::vec3(42.0f, m_atomicBomb->GetPosition().y - (TimeManager::GetDeltaTime() * 10.0f), -10.0f));

		if (m_atomicBomb->GetPosition().y < 20.0f)
		{
			m_currState = BOMB_EXPLOSION;
		
			
		}

		m_bomber->Render(cam);
		m_atomicBomb->Render(cam);

		break;

	case BOMB_EXPLOSION:
		if (!m_shakeEffect)
		{
			PostProcessingManager::SetState(PostProcessingManager::ATOMIC);
			m_shakeEffect = true;
			m_soundManager->PlaySFX("nuke");
		}

		m_t += TimeManager::GetDeltaTime() * 1.0f;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUseProgram(m_shader);

		glUniform1f(m_uniforms[SCREEN_WIDTH], VideoManager::Get()->GetWidth());
		glUniform1f(m_uniforms[SCREEN_HEIGHT], VideoManager::Get()->GetHeight());
		glUniform1f(m_uniforms[T], m_t);
	
	
	
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glUseProgram(0);

		glDisable(GL_BLEND);

		if (m_t > 1.0f)
		{
			Background::SetIsPostNuclear(true);
		}


		break;

	default:
		break;
	}

	m_bomber->Render(cam);
}



