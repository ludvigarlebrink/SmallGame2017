#include "Background.h"


bool Background::m_isPostNuclear = false;


Background::Background()
{
	m_backgroundType = 0;
	InitBackground();
	Init();

	m_t = 0;
}


Background::~Background()
{
}


void Background::UpdateAndRender()
{
	switch (m_backgroundType)
	{
	case GRAND_CANYON:
		UpdateGrandCanyon();
		break;
	case PIRATE:
		break;
	case PARTY:
		break;
	default:
		break;
	}
}


void Background::SetBackground(uint32_t backgroundType)
{
	m_backgroundType = backgroundType;
	InitBackground();
}


//::.. HELP FUNCTIONS ..:://
void Background::UpdateGrandCanyon()
{
	float deltaHeight = VideoManager::Get()->GetHeight() / 1080.0f;
	float deltaWidth = VideoManager::Get()->GetWidth() / 1920.0f;

	m_sprites[1].SetPosition(m_sprites[1].GetPosX() - (TimeManager::GetDeltaTime() * 5.0f * deltaWidth), m_sprites[1].GetPosY());
	if (m_sprites[1].GetPosX() < -1200.0f * deltaWidth)
	{
		m_sprites[1].SetPosition(1200.0f * deltaWidth, m_sprites[1].GetPosY());
	}

	m_sprites[2].SetPosition(m_sprites[2].GetPosX() - (TimeManager::GetDeltaTime() * 5.0f * deltaWidth), m_sprites[2].GetPosY());
	if (m_sprites[2].GetPosX() < -1200.0f * deltaWidth)
	{
		m_sprites[2].SetPosition(1200.0f * deltaWidth, m_sprites[2].GetPosY());
	}

	m_sprites[3].SetPosition(m_sprites[3].GetPosX() - (TimeManager::GetDeltaTime() * 5.0f * deltaWidth), m_sprites[3].GetPosY());
	if (m_sprites[3].GetPosX() < -1200.0f * deltaWidth)
	{
		m_sprites[3].SetPosition(1200.0f * deltaWidth, m_sprites[3].GetPosY());
	}

	m_sprites[4].SetPosition(m_sprites[4].GetPosX() - (TimeManager::GetDeltaTime() * 20.0f * deltaWidth), m_sprites[4].GetPosY());
	if (m_sprites[4].GetPosX() < -1350.0f * deltaWidth)
	{
		m_sprites[4].SetPosition(1350.0f * deltaWidth, m_sprites[4].GetPosY());
	}

	m_sprites[5].SetPosition(m_sprites[5].GetPosX() - (TimeManager::GetDeltaTime() * 20.0f * deltaWidth), m_sprites[5].GetPosY());
	if (m_sprites[5].GetPosX() < -1350.0f * deltaWidth)
	{
		m_sprites[5].SetPosition(1350.0f * deltaWidth, m_sprites[5].GetPosY());
	}

	if (!m_isPostNuclear)
	{
		for (uint32_t i = 0; i < 7; i++)
		{
			m_sprites[i].Render();
		}
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		glUseProgram(m_shader);
	
		glUniform1f(m_uniforms[TIME], m_t);
		glUniform2f(m_uniforms[RESOLUTION], VideoManager::Get()->GetWidth(), VideoManager::Get()->GetHeight());
		glUniform1f(m_uniforms[ALPHA], 1.0f);
	
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	
		glUseProgram(0);
	
		glDisable(GL_BLEND);

		glEnable(GL_DEPTH_TEST);

		m_sprites[6].SetIsGreyscale(true);
		m_sprites[6].Render();

		m_t += TimeManager::GetDeltaTime() * 0.14f;
	}

}


void Background::UpdatePirate()
{
}


void Background::UpdateParty()
{
}


void Background::InitBackground()
{
	float deltaHeight = VideoManager::Get()->GetHeight() / 1080.0f;
	float deltaWidth = VideoManager::Get()->GetWidth() / 1920.0f;

	switch (m_backgroundType)
	{
	case GRAND_CANYON:
		m_sprites.resize(7);

		m_sprites[0].SetTexture(".\\Assets\\Sprites\\GCBack.png");
		m_sprites[0].SetSize(VideoManager::Get()->GetWidth(), VideoManager::Get()->GetHeight());

		m_sprites[1].SetTexture(".\\Assets\\Sprites\\GCCloud3.png");
		m_sprites[1].SetSize(175 * deltaWidth, 65 * deltaHeight);
		m_sprites[1].SetPosition(900 * deltaWidth, 10 * deltaHeight);

		m_sprites[2].SetTexture(".\\Assets\\Sprites\\GCCloud2.png");
		m_sprites[2].SetSize(272 * deltaWidth, 116 * deltaHeight);
		m_sprites[2].SetPosition(-900 * deltaWidth, 10 * deltaHeight);

		m_sprites[3].SetTexture(".\\Assets\\Sprites\\GCCloud5.png");
		m_sprites[3].SetSize(234 * deltaWidth, 96 * deltaHeight);
		m_sprites[3].SetPosition(0 * deltaWidth, 100 * deltaHeight);

		m_sprites[4].SetTexture(".\\Assets\\Sprites\\GCCloud1.png");
		m_sprites[4].SetSize(500 * deltaWidth, 242 * deltaHeight);
		m_sprites[4].SetPosition(-700 * deltaWidth, 200 * deltaHeight);

		m_sprites[5].SetTexture(".\\Assets\\Sprites\\GCCloud4.png");
		m_sprites[5].SetSize(762 * deltaWidth, 360 * deltaHeight);
		m_sprites[5].SetPosition(700 * deltaWidth, 300 * deltaHeight);

		m_sprites[6].SetTexture(".\\Assets\\Sprites\\GCFront.png");
		m_sprites[6].SetSize(VideoManager::Get()->GetWidth(), VideoManager::Get()->GetHeight());

		break;
	case PIRATE:
		break;
	case PARTY:
		break;
	default:
		break;
	}
}

void Background::SetIsPostNuclear(bool value)
{
	m_isPostNuclear = value;
}


void Background::Init()
{

	std::string shaders[2];
	shaders[0] = ".\\Assets\\GLSL\\NuclearShader.vert";
	shaders[1] = ".\\Assets\\GLSL\\NuclearShader.frag";

	uint32_t shaderTypes[2];
	shaderTypes[0] = ShaderManager::VERT_SHADER;
	shaderTypes[1] = ShaderManager::FRAG_SHADER;


	m_shader = ShaderManager::CreateAndAttachShaders("Nuclear", shaders, shaderTypes, 2);

	glBindAttribLocation(m_shader, 0, "Position");

	ShaderManager::LinkAndValidate("Nuclear");

	m_uniforms[TIME] = glGetUniformLocation(m_shader, "Time");
	m_uniforms[RESOLUTION] = glGetUniformLocation(m_shader, "Resolution");
	m_uniforms[ALPHA] = glGetUniformLocation(m_shader, "Alpha");

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
