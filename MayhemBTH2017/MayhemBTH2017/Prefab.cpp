#include "Prefab.h"



Prefab::Prefab()
{

//	Init();
}


Prefab::~Prefab()
{

}

void Prefab::Update()
{
}


void Prefab::Render(Camera & cam)
{
	glUseProgram(m_shaderProgram);

	glUniformMatrix4fv(m_uniforms[M], 1, GL_FALSE, &m_transform.GetModelMatrix()[0][0]);
	glUniformMatrix4fv(m_uniforms[V], 1, GL_FALSE, &cam.GetView()[0][0]);
	glUniformMatrix4fv(m_uniforms[P], 1, GL_FALSE, &cam.GetProjection()[0][0]);
	
	m_animController->Update(m_uniforms[JOINTS]);

	m_mesh->Render();
}

//::.. HELP FUNCTIONS ..:://
void Prefab::Init()
{
	m_transform.SetScale(glm::vec3(1, 1, 1));
	m_transform.SetPosition(glm::vec3(0.0f, 0.0f, 11.0f));

	std::string * shaders = new std::string[2];
	uint32_t * types = new uint32_t[2];
	
	shaders[0] = ".\\Assets\\GLSL\\SkeletalAnimation.vert";
	shaders[1] = ".\\Assets\\GLSL\\SkeletalAnimation.frag";

	types[0] = ShaderManager::VERT_SHADER;
	types[1] = ShaderManager::FRAG_SHADER;

	m_shaderProgram = ShaderManager::CreateAndAttachShaders("AnimToon", shaders, types, 2);

	glBindAttribLocation(m_shaderProgram, 0, "Position");
	glBindAttribLocation(m_shaderProgram, 1, "Normal");
	glBindAttribLocation(m_shaderProgram, 2, "TexCoordsAlpha");
	glBindAttribLocation(m_shaderProgram, 3, "JointIndex");
	glBindAttribLocation(m_shaderProgram, 4, "JointWeight");

	ShaderManager::LinkAndValidate("AnimToon");

	m_uniforms[M] = glGetUniformLocation(m_shaderProgram, "M");
	m_uniforms[V] = glGetUniformLocation(m_shaderProgram, "V");
	m_uniforms[P] = glGetUniformLocation(m_shaderProgram, "P");
	m_uniforms[JOINTS] = glGetUniformLocation(m_shaderProgram, "Joints");



}

//::.. GET FUNCTIONS ..:://
const char * Prefab::GetName() const
{
	return m_name;
}


const Transform & Prefab::GetTransform() const
{
	return m_transform;
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


void Prefab::SetTransform(const Transform & transform)
{
	m_transform = transform;
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
