#ifndef __PREFAB_H__
#define __PREFAB_H__


#include "Transform.h"
#include "Mesh.h"
#include "AnimController.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Material.h"


class Prefab
{
public:
	enum Space
	{
		SPACE_LOCAL = 0,
		SPACE_GLOBAL
	};

	Prefab();
	virtual ~Prefab();

	void Update();
	void Render(Camera& cam);

	void Create();
	void Free();

	//::.. MODIFY FUNCTIONS ..:://
	void Move(glm::vec3 pos, uint32_t space = SPACE_LOCAL);
	void Move(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void Rotate(glm::vec3 rot, uint32_t space = SPACE_LOCAL);
	void Rotate(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void Scale(glm::vec3 scale, uint32_t space = SPACE_LOCAL);
	void Scale(float x, float y, float z, uint32_t space = SPACE_LOCAL);

	//::.. GET FUNCTIONS ..:://
	const char * GetName() const;
	const glm::vec3 GetRotation();
	const glm::vec3 GetScale();
	const glm::vec3 GetPosition();
	const Transform& GetTransform() const;
	Mesh * GetMesh() const;
	AnimController * GetAnimController() const;

	//::.. SET FUNCTIONS ..:://
	void SetName(const char * name);
	void SetTransform(const Transform& transform, uint32_t space = SPACE_LOCAL);
	void SetPosition(glm::vec3 pos, uint32_t space = SPACE_LOCAL);
	void SetPosition(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void SetRotation(glm::vec3 rot, uint32_t space = SPACE_LOCAL);
	void SetRotation(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void SetScale(glm::vec3 scale, uint32_t space = SPACE_LOCAL);
	void SetScale(float x, float y, float z, uint32_t space = SPACE_LOCAL);
	void SetMesh(Mesh * mesh);
	void SetAnimController(AnimController * animController);
	void SetShaderProgram(const char * programName);
	void SetMaterial(Material * material);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	enum Uniforms
	{
		M,
		V,
		P,
		JOINTS,
		ALBEDO_MAP,
		NORMAL_MAP,
		NR_UNIFORMS
	};

	bool				m_hasBeenCreated;
	bool				m_isEnabled;

	const char *		m_name;
	
	Transform			m_localTx;
	Transform			m_globalTx;

	Mesh *				m_mesh;
	const char *		m_shaderProg;
	AnimController *	m_animController;
	Material *			m_material;
	GLuint				m_shaderProgram;
	GLuint				m_uniforms[NR_UNIFORMS];
};


#endif 