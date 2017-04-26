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

	glUniformMatrix4fv(m_uniforms[M], 1, GL_FALSE, &m_localTx.GetModelMatrix()[0][0]);
	glUniformMatrix4fv(m_uniforms[V], 1, GL_FALSE, &cam.GetView()[0][0]);
	glUniformMatrix4fv(m_uniforms[P], 1, GL_FALSE, &cam.GetProjection()[0][0]);
	
	m_animController->Update(m_uniforms[JOINTS]);

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

	m_localTx.SetScale(glm::vec3(4.0f, 4.0f, 4.0f));
	m_localTx.SetPosition(glm::vec3(0.0f, 0.0f, 15.0f));
	m_localTx.SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));

	std::string * shaders = new std::string[2];
	uint32_t * types = new uint32_t[2];

	if (m_animController != nullptr)
	{
		shaders[0] = ".\\Assets\\GLSL\\SkeletalAnimation.vert";
	}
	else
	{
		shaders[0] = ".\\Assets\\GLSL\\ToonShader.vert";
	}

	shaders[1] = ".\\Assets\\GLSL\\ToonShader.frag";

	types[0] = ShaderManager::VERT_SHADER;
	types[1] = ShaderManager::FRAG_SHADER;

	if (m_animController != nullptr)
	{
		m_shaderProg = "AnimToon";
	}
	else
	{
		m_shaderProg = "Toon";
	}

	m_shaderProgram = ShaderManager::CreateAndAttachShaders(m_shaderProg, shaders, types, 2);

	delete[] shaders;
	delete[] types;

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

	if (m_animController != nullptr)
	{
		m_uniforms[JOINTS] = glGetUniformLocation(m_shaderProgram, "Joints");
	}

	m_hasBeenCreated = true;
}

void Prefab::Free()
{
}


//::.. MODIFY FUNCTIONS ..:://
void Prefab::Move(glm::vec3 pos, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetPosition(glm::vec3(m_localTx.GetPosition().x + pos.x, 
			m_localTx.GetPosition().y + pos.y, m_localTx.GetPosition().z + pos.z));
	}
	else
	{
		m_globalTx.SetPosition(glm::vec3(m_globalTx.GetPosition().x + pos.x,
			m_globalTx.GetPosition().y + pos.y, m_globalTx.GetPosition().z + pos.z));
	}
}


void Prefab::Move(float x, float y, float z, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetPosition(glm::vec3(m_localTx.GetPosition().x + x,
			m_localTx.GetPosition().y + y, m_localTx.GetPosition().z + z));
	}
	else
	{
		m_globalTx.SetPosition(glm::vec3(m_globalTx.GetPosition().x + x,
			m_globalTx.GetPosition().y + y, m_globalTx.GetPosition().z + z));
	}
}


void Prefab::Rotate(glm::vec3 rot, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetRotation(glm::vec3(m_localTx.GetRotation().x + rot.x,
			m_localTx.GetRotation().y + rot.y, m_localTx.GetRotation().z + rot.z));
	}
	else
	{
		m_globalTx.SetRotation(glm::vec3(m_globalTx.GetRotation().x + rot.x,
			m_globalTx.GetRotation().y + rot.y, m_globalTx.GetRotation().z + rot.z));
	}
}


void Prefab::Rotate(float x, float y, float z, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetRotation(glm::vec3(m_localTx.GetRotation().x + x,
			m_localTx.GetRotation().y + y, m_localTx.GetRotation().z + z));
	}
	else
	{
		m_globalTx.SetRotation(glm::vec3(m_globalTx.GetRotation().x + x,
			m_globalTx.GetRotation().y + y, m_globalTx.GetRotation().z + z));
	}
}


void Prefab::Scale(glm::vec3 scale, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetScale(glm::vec3(m_localTx.GetScale().x + scale.x,
			m_localTx.GetScale().y + scale.y, m_localTx.GetScale().z + scale.z));
	}
	else
	{
		m_globalTx.SetScale(glm::vec3(m_globalTx.GetScale().x + scale.x,
			m_globalTx.GetScale().y + scale.y, m_globalTx.GetScale().z + scale.z));
	}
}


void Prefab::Scale(float x, float y, float z, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetScale(glm::vec3(m_localTx.GetScale().x + x,
			m_localTx.GetScale().y + y, m_localTx.GetScale().z + z));
	}
	else
	{
		m_globalTx.SetScale(glm::vec3(m_globalTx.GetScale().x + x,
			m_globalTx.GetScale().y + y, m_globalTx.GetScale().z + z));
	}
}


//::.. GET FUNCTIONS ..:://
const char * Prefab::GetName() const
{
	return m_name;
}


const Transform & Prefab::GetTransform() const
{
	return m_localTx;
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
void Prefab::SetName(const char * name)
{
	m_name = name;
}


void Prefab::SetTransform(const Transform & transform, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx = transform;
	}
	else
	{
		m_globalTx = transform;
	}
}


void Prefab::SetPosition(glm::vec3 pos, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetPosition(pos);
	}
	else
	{
		m_globalTx.SetPosition(pos);
	}
}


void Prefab::SetPosition(float x, float y, float z, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetPosition(x, y, z);
	}
	else
	{
		m_globalTx.SetPosition(x, y, z);
	}
}


void Prefab::SetRotation(glm::vec3 rot, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetRotation(rot);
	}
	else
	{
		m_globalTx.SetRotation(rot);
	}
}


void Prefab::SetRotation(float x, float y, float z, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetRotation(x, y, z);
	}
	else
	{
		m_globalTx.SetRotation(x, y, z);
	}
}


void Prefab::SetScale(glm::vec3 scale, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetScale(scale);
	}
	else
	{
		m_globalTx.SetScale(scale);
	}
}


void Prefab::SetScale(float x, float y, float z, uint32_t space)
{
	if (space == SPACE_LOCAL)
	{
		m_localTx.SetScale(x, y, z);
	}
	else
	{
		m_globalTx.SetScale(x, y, z);
	}
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


//::.. HELP FUNCTIONS ..:://
void Prefab::Init()
{
	m_hasBeenCreated	= false;
	m_isEnabled			= true;

	m_mesh				= nullptr;
	m_animController	= nullptr;
	m_material			= nullptr;

	for (uint32_t i = 0; i < NR_UNIFORMS; i++)
	{
		m_uniforms[i] = 0;
	}
}
