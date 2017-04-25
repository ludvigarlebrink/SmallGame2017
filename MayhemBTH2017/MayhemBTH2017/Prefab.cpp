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
	if (m_animController != nullptr)
	{
		m_animController->Update();
	}
}


void Prefab::Render(const Camera & cam)
{

	if (m_material != nullptr)
	{
		m_material->Bind();
	}

	if (m_mesh != nullptr)
	{
		m_mesh->Render();
	}
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

//::.. HELP FUNCTIONS ..:://
void Prefab::Init()
{
	m_mesh				= nullptr;
	m_shaderProg		= nullptr;
	m_animController	= nullptr;
	m_material			= nullptr;
}
