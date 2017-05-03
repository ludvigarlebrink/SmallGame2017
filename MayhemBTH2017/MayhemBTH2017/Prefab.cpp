#include "Prefab.h"



Prefab::Prefab()
{
	Init();
}


Prefab::~Prefab()
{

}

void Prefab::Update()
{
}


void Prefab::Render(Camera & cam)
{
	if (!m_hasBeenCreated || !m_isEnabled)
	{
		return;
	}


	glUseProgram(m_shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_albedoID);

	glUniformMatrix4fv(m_uniforms[M], 1, GL_FALSE, &m_tx[SPACE_LOCAL].GetModelMatrix()[0][0]);
	glUniformMatrix4fv(m_uniforms[V], 1, GL_FALSE, &cam.GetView()[0][0]);
	glUniformMatrix4fv(m_uniforms[P], 1, GL_FALSE, &cam.GetProjection()[0][0]);
	
	if (m_hasAnimation)
	{
		m_animController->QuickUpdate(m_uniforms[JOINTS]);
		glUniform1i(m_uniforms[ALBEDO_MAP], 0);
	}


	m_mesh->Render();

	glUseProgram(0);
}

//::.. HELP FUNCTIONS ..:://
void Prefab::Create()
{
	if (m_hasBeenCreated)
	{
		return;
	}

	m_tx[SPACE_LOCAL].SetScale(glm::vec3(4.0f, 4.0f, 4.0f));
	m_tx[SPACE_LOCAL].SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_tx[SPACE_LOCAL].SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));


	std::string shaders[2];
	uint32_t types[2];

	if (m_animController != nullptr)
	{
		shaders[0] = ".\\Assets\\GLSL\\SkeletalAnimation.vert";
		shaders[1] = ".\\Assets\\GLSL\\ToonShader.frag";
	}
	else
	{
		shaders[0] = ".\\Assets\\GLSL\\DebugShader.vert";
		shaders[1] = ".\\Assets\\GLSL\\DebugShader.frag";
	}

	types[0] = ShaderManager::VERT_SHADER;
	types[1] = ShaderManager::FRAG_SHADER;

	if (m_animController != nullptr)
	{
		m_shaderProg = "AnimToon";
		m_hasAnimation = true;
	}
	else
	{
		m_shaderProg = "Toon";
		m_hasAnimation = false;
	}

	m_shaderProgram = ShaderManager::CreateAndAttachShaders(m_shaderProg, shaders, types, 2);


	glBindAttribLocation(m_shaderProgram, 0, "Position");
	glBindAttribLocation(m_shaderProgram, 1, "Normal");
	glBindAttribLocation(m_shaderProgram, 2, "TexCoordsAlpha");

	if (m_animController != nullptr)
	{
		glBindAttribLocation(m_shaderProgram, 3, "JointIndex");
		glBindAttribLocation(m_shaderProgram, 4, "JointWeight");
	}

	ShaderManager::LinkAndValidate(m_shaderProg);

	m_uniforms[M] = glGetUniformLocation(m_shaderProgram, "M");
	m_uniforms[V] = glGetUniformLocation(m_shaderProgram, "V");
	m_uniforms[P] = glGetUniformLocation(m_shaderProgram, "P");

	if (m_hasAnimation)
	{
		m_uniforms[JOINTS] = glGetUniformLocation(m_shaderProgram, "Joints");
		m_uniforms[ALBEDO_MAP] = glGetUniformLocation(m_shaderProgram, "AlbedoMap");
	}


	m_hasBeenCreated = true;
}

void Prefab::Free()
{
}


//::.. MODIFY FUNCTIONS ..:://
void Prefab::Move(glm::vec3 pos, uint32_t space)
{
	m_tx[space].SetPosition(glm::vec3(m_localTx.GetPosition().x + pos.x,
		m_localTx.GetPosition().y + pos.y, m_localTx.GetPosition().z + pos.z));
}


void Prefab::Move(float x, float y, float z, uint32_t space)
{
	m_tx[space].SetPosition(glm::vec3(m_localTx.GetPosition().x + x,
		m_localTx.GetPosition().y + y, m_localTx.GetPosition().z + z));
}


void Prefab::Rotate(glm::vec3 rot, uint32_t space)
{
	m_tx[space].SetRotation(glm::vec3(m_localTx.GetRotation().x + rot.x,
		m_localTx.GetRotation().y + rot.y, m_localTx.GetRotation().z + rot.z));
}


void Prefab::Rotate(float x, float y, float z, uint32_t space)
{
	m_tx[space].SetRotation(glm::vec3(m_localTx.GetRotation().x + x,
		m_localTx.GetRotation().y + y, m_localTx.GetRotation().z + z));
}


void Prefab::Scale(glm::vec3 scale, uint32_t space)
{
	m_tx[space].SetScale(glm::vec3(m_localTx.GetScale().x + scale.x,
		m_localTx.GetScale().y + scale.y, m_localTx.GetScale().z + scale.z));
}


void Prefab::Scale(float x, float y, float z, uint32_t space)
{
		m_tx[space].SetScale(glm::vec3(m_localTx.GetScale().x + x,
			m_localTx.GetScale().y + y, m_localTx.GetScale().z + z));
}


//::.. GET FUNCTIONS ..:://
bool Prefab::GetIsEnabled() const
{
	return m_isEnabled;
}


const char * Prefab::GetName() const
{
	return m_name;
}


Transform & Prefab::GetTransform(uint32_t space)
{
	return m_tx[space];
}


glm::vec3 Prefab::GetPosition(uint32_t space) 
{
	return m_tx[space].GetPosition();
}


glm::vec3 Prefab::GetRotation(uint32_t space)
{
	return m_tx[space].GetRotation();
}


glm::vec3 Prefab::GetScale(uint32_t space)
{
	return m_tx[space].GetScale();
}


Mesh * Prefab::GetMesh() const
{
	return m_mesh;
}


AnimController * Prefab::GetAnimController() const
{
	return m_animController;
}


//::.. SET FUNCTIONS ..:://
void Prefab::SetIsEnabled(bool enabled)
{
	m_isEnabled = enabled;
}


void Prefab::SetName(const char * name)
{
	m_name = name;
}


void Prefab::SetTransform(const Transform & transform, uint32_t space)
{
	m_tx[space] = transform;
}


void Prefab::SetPosition(glm::vec3 pos, uint32_t space)
{
	m_tx[space].SetPosition(pos);
}


void Prefab::SetPosition(float x, float y, float z, uint32_t space)
{
	m_tx[space].SetPosition(x, y, z);
}


void Prefab::SetRotation(glm::vec3 rot, uint32_t space)
{
	m_tx[space].SetRotation(rot);
}


void Prefab::SetRotation(float x, float y, float z, uint32_t space)
{
	m_tx[space].SetRotation(x, y, z);
}


void Prefab::SetScale(glm::vec3 scale, uint32_t space)
{
	m_tx[space].SetScale(scale);
}


void Prefab::SetScale(float x, float y, float z, uint32_t space)
{
	m_tx[space].SetScale(x, y, z);
}


void Prefab::SetMesh(Mesh * mesh)
{
	m_mesh = mesh;
}


void Prefab::SetAnimController(AnimController * animController)
{
	m_animController = animController;
}


void Prefab::SetShaderProgram(const char * programName)
{
	m_shaderProg = programName;
}


void Prefab::SetMaterial(Material * material)
{
	m_material = material;
}

void Prefab::SetAlbedoID(GLuint id)
{
	m_albedoID = id;
}


//::.. HELP FUNCTIONS ..:://
void Prefab::Init()
{
	m_hasBeenCreated	= false;
	m_isEnabled			= true;
	m_hasAnimation		= false;

	m_mesh				= nullptr;
	m_animController	= nullptr;
	m_material			= nullptr;

	for (uint32_t i = 0; i < NUM_UNIFORMS; i++)
	{
		m_uniforms[i] = 0;
	}
}
